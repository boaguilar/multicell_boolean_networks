import sys
import os
import subprocess
import numpy
import shutil
import math
import xml.etree.ElementTree as ET

from xml.etree.ElementTree import Element, SubElement, Comment
from xml.dom import minidom
import csv

def NumCellsFromXYZR (  xyzrt_file , typeid ) :
    with open( xyzrt_file, 'r') as f:
       first_line = f.readline()
       contador = 0 
       for line in f :
           
           celldata = line.strip().split()
           if ( celldata[-1] == str(typeid)  ) : # cancer  cells have id = 0 (bad practice)
                contador = contador + 1 

       return contador

def GetExpTrajectoriesFromOutput( celltype_name ,
                                 biocellion_output_file, Ngenes ):
    """ Extract gene expression trajectory from simulation 
    celltype_name   : Name of the cell type {BN_0, BN_1, BN_2, BN_3, BN_4}
    biocellion_output_file : File printed by the biocellion model of PDAC
    Ngenes : Number of genes.
    """
    gene_expression = []
    
    with open(biocellion_output_file, 'r') as bcfile :
        genecount = [ 0 for x in range(Ngenes) ]
        cont = 0
        for line in bcfile :
            if celltype_name in line :
                genesum = int(  line.strip().split(":")[-1] )
                genecount[ cont ] = genesum
                cont =  cont + 1

            if ( cont == Ngenes ) :
                gene_expression.append( genecount )
                genecount = [ 0 for x in range( Ngenes ) ]
                cont = 0
     
    return gene_expression  

def GetAVGExpressionFromOutput( SimulationSteps , celltype_name ,
                                 biocellion_output_file, Ngenes ):
    """ Compute average gene expression from simulation of PDAC model
    SimulationSteps : The number of time steps considered for the Average.
    celltype_name   : Name of the cell type {BN_0, BN_1, BN_2, BN_3, BN_4}
    biocellion_output_file : File printed by the biocellion model of PDAC
    """
    gene_expression = []
    
    with open(biocellion_output_file, 'r') as bcfile :
        genecount = [ 0 for x in range(Ngenes) ]
        cont = 0 
        for line in bcfile :
            if celltype_name in line :
                genesum = int(  line.strip().split(":")[-1] )
                genecount[ cont ] = genesum
                cont =  cont + 1 
            
            if ( cont == Ngenes ) :
                gene_expression.append( genecount )
                genecount = [ 0 for x in range( Ngenes ) ]
                cont = 0

    # add the last steps
    Nsteps =  len( gene_expression )
    gene_sum = [ 0.0 for _ in range(Ngenes) ]
    for i in range( Nsteps - SimulationSteps, Nsteps) :
        for j in  range( Ngenes ) :
            gene_sum[j] = gene_sum[j] + gene_expression[i][j]

    for j in range( Ngenes ) : 
         gene_sum[j] = float( gene_sum[j] ) / float( SimulationSteps )
  
    return  gene_sum 



def GetAVGcytokineConcentration( SimulationSteps , name,
                                 biocellion_output_file, output_dir ):
    """ Compute average concentration of a cytokine a from simulation of PDAC model
    SimulationSteps : The number of time steps considered for the Average.
    name : Name of the cytokine
    biocellion_output_file : File printed by the biocellion model of PDAC
    output_dir : name of directory in which the average will be printed
    The output filename will by "output_dir  + name  +'_concentration.txt'"
    """
    avg_concentration = []
    with open(biocellion_output_file, 'r') as bcfile :
        for line in bcfile :
            if name in line :
                cytokine = float(  line.strip().split(":")[-1] )
                avg_concentration.append( cytokine )

    filename = output_dir  + name  +'_concentration.txt'
    myfile = open(filename, 'a' )

    avg_cytokine = 0.0
    for i in range( -1 ,  -SimulationSteps -1   ,  -1 ) :
        avg_cytokine = avg_cytokine + avg_concentration[i] 

    myfile.write( '{0:12.6f}'.format( avg_cytokine/float(SimulationSteps)) + '\n')
    myfile.close()


def num_to_bin(num, nbits):
    """From decimal number to binary array.
    num : decimal number
    nbits :  number of bits for the output array

    The most significant digit is located in the last element of the binarray
    """
    binary = []
    while num != 0:
        bit = num % 2
        binary.append(bit)
        num = num // 2

    binarray = [0 for x in range(nbits)]
    Nbits = len(binary)
    for i in range(Nbits):
        binarray[nbits - i - 1] = binary[i]

    return binarray

def PoissonPP( rt, L, dim ):
    """Determines the number of events (N) in a rectangular region,
    given the rate rt  and the dimensions in 3D: L = Lx=Ly=Lz.
    Returns a <Nx3> NumPy array.
    """
    avgN = rt * (L ** dim )
    N = numpy.random.poisson( avgN  )
    P = numpy.random.uniform(0, L, (N,dim) )
    return(P)

def EffectiveDensity_VoidModels ( Lxyz, Lambda_input, ParentPoints , Rexpunge, h_vol ) :
    """Estimate the intensity (lambda) that should be used when cells inside spheres
    with radius   Rxpunge and     cetered in Parent Points are removed. 
    This intensity will be used to generate  a poisson random process,
    if the desired density Lamnda_input is wanted in the void process.
    The relation ship is Lamnda = Lamnda_input ( 1 / (1 - f) ) 
    where f is ratio of void Volume and volume of the systems.
    Parameteres:
    Lxyz           : Length of the simulations domain
    Lambda_input   : density of cells
    ParentPoints   : density of parent cancer cells
    Rexpunge       : Radius for  expunged cells
    h_vol          : Grid ssize to estimate volume inside expunge spheres 
    """

    h3 = h_vol * h_vol *h_vol
    Rexpunge2 =  Rexpunge ** 2
    Nxyz =  int( math.ceil( Lxyz / h_vol ) )
    L = int( math.ceil( Rexpunge / h_vol  ) )
    myGrid =  [[[0 for col in range(Nxyz)] for row in range(Nxyz)] for x in range(Nxyz)]
    Sum  =  0.0

    for point in ParentPoints :

        i=math.floor(point[0]/h_vol)
        j=math.floor(point[1]/h_vol)
        k=math.floor(point[2]/h_vol)
        Disp = range( -L, L+1)

        for ii in Disp :
            for jj in Disp :
                for kk in Disp :
                    I = int(i + ii); J = int(j + jj); K = int(k + kk)

                    rx = float(I)*h_vol + 0.5*h_vol
                    ry = float(J)*h_vol + 0.5*h_vol
                    rz = float(K)*h_vol + 0.5*h_vol

                    r2 = (rx - point[0])**2 + (ry - point[1])**2 + (rz - point[2])**2
                    if ( r2 <=  Rexpunge2 ) :

                        if ( I >= Nxyz) : I = I % Nxyz
                        if ( J >= Nxyz) : J = J % Nxyz
                        if ( K >= Nxyz) : K = K % Nxyz

                        if ( myGrid[I][J][K] == 0 ) :
                            Sum = Sum + 1.0
                            myGrid[I][J][K] = 1

    ratio = Sum * h3 / ( Lxyz * Lxyz * Lxyz )
    return Lambda_input * ( 1.0 /( 1.0 - ratio ) ) 


def GenerateVoidProcessStroma( Lxyz, Lambda, ParentPoints , Rexpunge ) :
    """ Generate the coordinate of stromal cells using 

    Parameteres:
    Lxyz         : Length of the simulations domain 
    Lambda       : density of cells
    ParentPoints : cluster centers for expunging stromal cells 
    Rexpunge     : Radiis of spherical voids
  
    Return a list of points from a Void Process.
    """

    dim = 3
    R2 = Rexpunge * Rexpunge
    Points  = PoissonPP(Lambda, Lxyz, dim ) # generate points
    NPoints = len ( Points )
    flags = [ 0 for x in range( NPoints ) ]
    OutPoints = []
    for point in Points:

        voidflag = True
        for parent in ParentPoints :
            r2 = ( point[0] - parent[0])**2 + ( point[1] - parent[1])**2 + ( point[2] - parent[2])**2
            if ( r2 <= R2 ) :
                voidflag = False
                break

        if voidflag :
            OutPoints.append( point)

    return OutPoints


def GenerateThomasProcessCancer( Lxyz, Lambda, Lambda_p, ParentPoints, sigma  ) :
    """ Generate points from the Thomas Process 
    Lxyz         : Length of the simulations domain 
    Lambda       : density of cells
    Lambda_p     : density of clusters ( or parents ) 
    ParentPoints : List of points that represents cluster centers 
    sigma        : covariance parameter 
    """

    dim = 3
    NumParents  = len( ParentPoints ) # Number of parents
    sigma2 = sigma * sigma
    avgNpercluster = Lambda / Lambda_p
    # generate the number of cells pero cluster
    NumChildren = numpy.random.poisson( avgNpercluster, NumParents )
    cov = [[ sigma2  , 0,  0 ], [0, sigma2, 0], [ 0, 0, sigma2  ]  ]

    Children = list()
    for i  in range(NumParents)  :
       M = NumChildren[i]

       if ( M > 0 ) :
          parent = ParentPoints[i]
          children_p  = numpy.random.multivariate_normal( parent, cov, M  )
          for x in children_p : Children.append( x)

    # fix periodic boundary conditions
    for point in Children :
       for i in range(dim) :
            if point[i] < 0.0 :
                point[i] = Lxyz + point[i]

            elif point[i] > Lxyz :
                point[i] = point[i] - Lxyz

    return Children


def UniformCellTypes( Ncells, a_labels, a_fractions  )  :
    """ Return an array with random labels from a_labels

    Parameteres:
    Ncells       : The desired number of cells, this will be the size of output array
    a_celltypes  : an array with the different labels (integer numbers) 
    a_fractions  : desired proportions of the corresponding labels ( number in <0,1])
                   a_celltypes and a_franctions must have the same size
    """
    celltypes = [-1 for x in range(Ncells) ]

    Ntypes = len(a_fractions)
    localsum = sum(a_fractions)
    new_fractions = [ x/localsum for x in a_fractions ]

    sumcum  = [ 0.0  for x in range( Ntypes  ) ]
    sumcum[0] =  new_fractions[0]
    for i in range( 1 , Ntypes  ):
         sumcum[i] = sumcum[i-1] + new_fractions[i]


    for cell in range(Ncells) :
        r = numpy.random.rand()

        for i in range(Ntypes) :
            if ( r <= sumcum[i] ) :
                break

        celltypes[ cell ]  = a_labels[i]

    return celltypes

def PrintXYZRTfromPoints ( OutFile , Points, CellTypes  ) :
   """Print and XYZRT file which for each line print  positions(X,Y,Z), radius, and type of a cell
   OutFile   : name of the xyzrt file 
   Points    : list with the xyz values that define positions of cells
   CellTypes : list with the labels that define cell types 

   """
   with open(OutFile, "w" ) as f :

      NumberCells = len( Points )

      f.write( str( NumberCells) + '\n' )
      for ii in range( NumberCells ) :
         point = Points[ii]
         mytype = CellTypes[ii]
         f.write(  "{0:.8} {1:.8} {2:.8} {3:.3} {4:d}".format( point[0] , point[1], point[2], 10.0, mytype  ) + '\n' )


def GenerateXYZRTfiles( OutFile, Lxyz, fractions, Lambda, rho_p, Lambda_max, rho_exp )  : 
    """Generate the xyzrt file ( 3D position, radius, and type) using 
    Thomas process for cancer cells and Void process for stromal cells
 
    Parameteres:
    OutFile      : name of the xyzrt file
    Lxyz         : Length of the simulations domain ( side )
    fractions    : an array with the desired fractions of cells
    Lambda       : Desired Density of cells 
    rho_p        : scaling factors to determine the density of cluster (Lamda_p = rho_p*Lambda)
    Lambda_max   : Desired Density of cancer cluster
    rho_exp      : scaling factor to determine the expunge radius ( R_exp = rho_exp * sigma ) 
    """

    fraction_cancer =  fractions[0]
    fraction_stroma = 1 - fraction_cancer
    fractions_other  = [ fractions[i] for i in range(1,len(fractions)) ]
 
    dim = 3
    h_vol = 2.0

    prefactor = 0.162338041953733 # 0.68 * ( 3 /(4*pi) ))

    Lambda_p = Lambda * rho_p * fraction_cancer
    sigma = ( prefactor/( rho_p * Lambda_max ) ) ** (1/3.0)

    Rexpunge = rho_exp * sigma

    Parents  = PoissonPP(Lambda_p, Lxyz, dim ) # generate parents
    new_lamda = EffectiveDensity_VoidModels (  Lxyz, fraction_stroma*Lambda, Parents, Rexpunge, h_vol)
    StromaCells = GenerateVoidProcessStroma( Lxyz, new_lamda, Parents, Rexpunge )
    CancerCells = GenerateThomasProcessCancer( Lxyz, fraction_cancer*Lambda, Lambda_p,  Parents, sigma  )
    StromaTypes = UniformCellTypes(len(StromaCells), [1,2,3,4], fractions_other )
    CellTypes = [0 for x in CancerCells] + StromaTypes
    AllCells = CancerCells + StromaCells
    PrintXYZRTfromPoints ( OutFile , AllCells  , CellTypes )

def add_mutations_pcc_stroma(xyzrt_file, output_stfile, gene_idxs, gene_probability, ctype, gene_idxs_s, gene_probability_s ):
    """ Generate random initial binary states files ( stfile) placing -1
    to genes that are mutated in randomly selected cells
    xyzrt_file         : xyzrt file that contains cell positions and types
    output_stfile      : output file with initial binary states
    gene_idxs          : list of genes that will be mutated
    gene_probability   : list of mutation probabilities for genes in "gene_idxs"
    ctype              : index of stroma cell type [1, 2  ... ]
    gene_idxs_s        : list of genes that will be mutated 
    gene_probability_s : mutation probabilities for genes in gene_idxs_c 
    """

    A_cells = []
    NumGenes =  44 
    fout = open( output_stfile, 'w' )
    Nmutations = len(gene_idxs)
    Nmutations_s = len(gene_idxs_s)

    with open( xyzrt_file, 'r') as f:
        first_line = f.readline()
        for line in f :
            v_state = numpy.random.randint(2, size = NumGenes )
            celldata = line.strip().split()
            if ( celldata[-1] == '0'  ) : # cance cells have id = 0
                for i in range(Nmutations) :
                    r = numpy.random.rand()
                    if ( r < gene_probability[i]) :
                         v_state[ gene_idxs[i] ] = -1
                    else :
                        if ( (gene_idxs[i] == 0) or (gene_idxs[i] == 1) ) :
                            v_state[ gene_idxs[i] ] = 1

            if ( celldata[-1] == str(ctype)  ) :# pcc 0, psc 1, cd4 2, tam 3, cd8 4
                for i in range(Nmutations_s) :
                    r = numpy.random.rand()
                    if ( r < gene_probability_s[i]) :
                         v_state[ gene_idxs_s[i] ] = -1

                         
            if ( celldata[-1] == '1'  ) : # stellate cells 
               v_state[0] = 0
            #elif ( celldata[-1] == '3'  ) : # macrophages cells
            #    v_state[0] = 1   # GMCSF 
            #    v_state[1] = 0   # IC        
            #    v_state[3] = 0   # IL1
            elif ( celldata[-1] == '4'  ) : # cd8 cells
                v_state[0] = 1
                v_state[1] = 1
                v_state[2] = 1
                v_state[3] = 1
               
                         
            fout.write(' '.join( [ str(x) for x in v_state] ) + '\n'  )
                

    fout.close()
    
    
def add_mutations_pccmut_psc( xyzrt_file, output_stfile, NumGenes, gene_idxs, gene_probability ):
    """ Generate random initial binary states files ( stfile) placing -1 
    to genes that are mutated in randomly selected cells
    xyzrt_file       : name of the xyzrt files that contains cell types
    output_stfile    : name of the file with initial binary states 
    gene_idxs        : list of genes that will be mutated
    gene_probability : list of mutation probabilities for genes in "gene_idxs"
    """ 
    A_cells = []
    fout = open( output_stfile, 'w' )
    Nmutations = len(gene_idxs)

    with open( xyzrt_file, 'r') as f:
       first_line = f.readline()
       for line in f :
           v_state = numpy.random.randint(2, size = NumGenes )
           celldata = line.strip().split()
           if ( celldata[-1] == '0'  ) : # cancer  cells have id = 0 (bad practice) 
               v_state[ 39 ] = 0 # TOXICITY signal from immune cells should  be zero
               for i in range(Nmutations) :
                    r = numpy.random.rand()
                    if ( r < gene_probability[i]) :
                         v_state[ gene_idxs[i] ] = -1
                    else :
                        if ( (gene_idxs[i] == 0) or (gene_idxs[i] == 1) ) :
                            v_state[ gene_idxs[i] ] = 1


           elif ( celldata[-1] == '1'  ) : # stellate cells
               v_state[0] = 0  # PPARg signal is zero
               v_state[1] = 0  # TNF signal is zero
               v_state[2] = 0  # IFNG signal is zero
               
               
            
           fout.write(' '.join( [ str(x) for x in v_state] ) + '\n'  )

    fout.close()

def GenerateCellsXYZRT( OutFile, Lxyz, Lambda ) :
    """ Create the xyzrt file used by biocellion model with Poisson distribution
    OutFile : output xyzrt file 
    Lxyz    : side of the cubic simulation domain
    Lambda  : desired density of points 
    """
    dim = 3
    CellPoints = PoissonPP(Lambda, Lxyz, dim ) # generate points 
    with open(OutFile, "w" ) as f :
        NumberCells = len( CellPoints )
        f.write( str( NumberCells) + '\n' )
        for point in CellPoints:
            f.write("{0:.8} {1:.8} {2:.8} {3:.3} {4:d}".format( point[0], point[1], point[2], 10.0, 0) + '\n' )


def output_id_cell( mydir , IniStep, FinStep, column  ):
   """ outputs a lists of cell 
   mydir   : directory in which  biocellio csv files are printed
   IniStep : initial step used for printing the list
   FinStep : final step
   colum   : the colum that will be printed  
   """

   NumSteps = (FinStep + 1) - IniStep
   SCORES = {}
   for step in range(IniStep, FinStep+1) :
       cvs_filename  = mydir  + "/cells."+ str(step) +".csv"
       #print step
       #with open( cvs_filename, 'rb') as csvfile:
       with open( cvs_filename, newline='' ) as csvfile:
           spamreader = csv.reader(csvfile, delimiter=',')
           for row in spamreader:
               if (row[0].isdigit()) :
                   cellid = int( row[0] ) ; # assume that index cell is the cell if ( fix me!!)
                   if ( step == IniStep ):
                        SCORES[ cellid  ] = [ -1 for x in xrange( FinStep + 1 )  ]
                   SCORES[cellid ][step] = int(row[column])
   return SCORES

def GenerateInitialBNs( xyzrt_file, output_stfile, NumGenes) :
    """ Generate initial random states for the Boolean networks ( 0s and 1s)
    
    """
    fout = open( output_stfile, 'w' )
    with open( xyzrt_file, 'r') as f:
        first_line = f.readline()
        for line in f :
            v_state = numpy.random.randint(2, size = NumGenes )
            fout.write(' '.join( [ str(x) for x in v_state] ) + '\n'  )

    fout.close()

def print_avg_cancer_scores(IniStep, FinStep, simulation_dir, output_dir ) :
    """ Prrint avergare "scores"  over a simulations trajectory
    Still in  progresss !!!!! 
    """
    Scores2 = output_id_cell( simulation_dir, IniStep, FinStep, 3, -1 )
    CellTypes = output_id_cell( simulation_dir, FinStep, FinStep,0, -1 )

    SCORES = {}
    for cell_id in  Scores2  :
        if ( CellTypes[cell_id][FinStep] == 0 ):
              SCORES[ cell_id  ] = [0.0 , 0.0, 0.0, 0.0 ]

    NumCancerCells = len( SCORES )
    NumSteps =  FinStep - IniStep  + 1
    filename = output_dir  + 'scores.txt'
    myfile = open( filename  , 'a' )

    prol_id  = 37 - 21    ## not good practice ( fix me!!!) 
    death_id  = 36 - 21
    auto_id  = 35 - 21

    for step in range( IniStep , FinStep + 1  ) :
        for cell_id in SCORES :
            binarray2  = list( reversed( num_to_bin( Scores2[cell_id][step] ,20 ) ))

            Prol = int(binarray2[ prol_id  ])
            Apop = int(binarray2[ death_id ])
            Auto = int(binarray2[ auto_id ])

            alpha = float(Prol + Apop + Auto)

            if alpha == 0:
                SCORES[cell_id][0] += 1.0
            else:
                SCORES[cell_id][1] += float(Prol / alpha)
                SCORES[cell_id][2] += float(Apop / alpha)
                SCORES[cell_id][3] += float(Auto / alpha)

    # compute average !!!
    AVG_SCORES = [0.0 , 0.0, 0.0, 0.0 ]
    for cell_id in sorted( SCORES ) :
        for ii in range(4) :
            AVG_SCORES[ii] += SCORES[ cell_id ][ii] / ( NumCancerCells * NumSteps  )

    myfile.write('{0:12.6f}{1:12.6f}{2:12.6f}{3:12.6f}'.format(AVG_SCORES[0], AVG_SCORES[1], AVG_SCORES[2], AVG_SCORES[3] ) + '\n' )
    myfile.close()


def compute_selected_expression_type( IniStep, FinStep, simulation_dir, gene_indexes, celltype): 
    """ Compute average ?? expression of genes in a given cell type over a trayectory
    InitStep, FinStep :  the time interval for data adquisition
    simulation_dir    :
    gene_indexes      : the ids for the genes that will be printed
    celltype          : the if of cell type 
    """
    Noutput = len( gene_indexes )
    Scores1 = output_id_cell( simulation_dir, IniStep, FinStep, 2, celltype  )
    Scores2 = output_id_cell( simulation_dir, IniStep, FinStep, 3, celltype  )

    NCells = len( Scores1 )
    if ( NCells <= 0 ) :
         return []

    NTimiSteps = FinStep - IniStep + 1
    count_gene = [0 for x in gene_indexes ]
    for step in range( IniStep , FinStep + 1  ) :
        for key in sorted(Scores1) :
            binarray1  = list( reversed( num_to_bin( Scores1[key][step], 21) ))
            binarray2  = list( reversed( num_to_bin( Scores2[key][step], 20) ))
            binstates = binarray1 + binarray2

            for i in range(Noutput) :
                count_gene[i]  +=  binstates[ gene_indexes[i] ]

    
    for i in range( Noutput ):
        count_gene[i] = float(count_gene[i]) / float( NCells * NTimiSteps )

    return  count_gene


def print_selected_expression_type(IniStep, FinStep, simulation_dir, output_dir, gene_indexes, celltype):
    """ SImilar than  the above equation  but prints the count in an file 
    """
    Noutput = len( gene_indexes )
    filename = output_dir  + 'BNstates_type'+ str(celltype)  +'.txt'

    Scores1 = output_id_cell( simulation_dir, IniStep, FinStep, 2, celltype  )
    Scores2 = output_id_cell( simulation_dir, IniStep, FinStep, 3, celltype  )

    NCells = len( Scores1 )
    if ( NCells <= 0 ) :
         with open( filename , "a") as text_file: 
            text_file.close() 

         return 

    NTimiSteps = FinStep - IniStep + 1

    count_gene = [0 for x in gene_indexes ]
    for step in range( IniStep , FinStep + 1  ) :
        for key in sorted(Scores1) :
            binarray1  = list( reversed( num_to_bin( Scores1[key][step], 21) ))
            binarray2  = list( reversed( num_to_bin( Scores2[key][step], 20) ))
            binstates = binarray1 + binarray2

            for i in range(Noutput) :
                count_gene[i]  +=  binstates[ gene_indexes[i] ]

    for i in range( Noutput ):
        count_gene[i] = float(count_gene[i]) / float( NCells * NTimiSteps )

    with open( filename , "a") as text_file:
        s = ' '
        text_file.write( s.join( str(x) for x in  count_gene ) + '\n' )
        text_file.close()


def print_selected_expression_type_trajetory (IniStep, FinStep, simulation_dir, output_dir, gene_indexes, celltype):
    """ Another version of the above function
    """

    Noutput = len( gene_indexes )
    filename = output_dir  + 'BNstates_type'+ str(celltype)  +'.txt'
   
    Scores1 = output_id_cell( simulation_dir, IniStep, FinStep, 2, celltype  )
    Scores2 = output_id_cell( simulation_dir, IniStep, FinStep, 3, celltype  )

    NCells = len( Scores1 )
    if ( NCells <= 0 ) :
         with open( filename , "a") as text_file: 
            text_file.close() 

         return 


    NTimiSteps = FinStep - IniStep + 1

    for step in range( IniStep , FinStep + 1  ) :
        count_gene = [0 for x in gene_indexes ]
        for key in sorted(Scores1) :

            binarray1  = list( reversed( num_to_bin( Scores1[key][step], 21) ))
            binarray2  = list( reversed( num_to_bin( Scores2[key][step], 20) ))
            binstates = binarray1 + binarray2
 
            for i in range(Noutput) :
                count_gene[i]  +=  binstates[ gene_indexes[i] ]

    
        for i in range( Noutput ):
            count_gene[i] = float(count_gene[i]) / float( NCells  )


        with open( filename , "a") as text_file:
            s = ' '
            text_file.write( s.join( str(x) for x in  count_gene ) + '\n' )
            text_file.close()


def output_id_cell( mydir , IniStep, FinStep, column , celltype ):
    """ Output a list of values ( defined by column number in cvs files ) 
    for an especific cell type
    mydir             :  directory in which all cell types are located
    InitStep, FinStep :  Steps for data adquisitions
    column            :  desired column of cvs files 
    celltype          :  id of cell type 
    """

    NumSteps = (FinStep + 1) - IniStep
    SCORES = {}

    for step in range(IniStep, FinStep+1) :
        cvs_filename  = mydir  + "/cells."+ str(step) +".csv"
        #print( cvs_filename )
        #print step
        with open( cvs_filename, newline='') as csvfile:
            spamreader = csv.reader(csvfile, delimiter=',')
            for row in spamreader: 
 
                if (row[1].isdigit()) :

                  mytype = int( row[0] )
                  if (celltype == -1 ) or ( celltype == mytype) :

                     cellid = int( row[1] ) ;
                     if ( step == IniStep ):
                         SCORES[ cellid  ] = [ -1 for x in range( FinStep + 1 )  ]

                     SCORES[cellid ][step] = int(row[column])

    return SCORES


def prettify(elem):
    """Return a pretty-printed XML string for the Element.
    """
    rough_string = ET.tostring(elem, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="  ")


def write_bcell_xml(OUTPUT_DIR, PARAMETERS, xmlname, SIMULATION_STEPS):
    # write the files for biocellion
    xml_file = open(xmlname, 'w')

    # Biocellion required parameters
    bcell_num_baseline = SIMULATION_STEPS  # Number of steps of the simulation
    bcell_nx = '16'  # size in x ( Num. of grid points
    bcell_ny = '16'
    bcell_nz = '16'
    bcell_partition_size = 16  # multiple of max(4,refine_ratio^(AMR_levels - 1)*2(minimum box size))
    bcell_path = OUTPUT_DIR
    bcell_interval = 1  # output interval
    bcell_start_x = 0  # start position from which results will be printed
    bcell_start_y = 0
    bcell_start_z = 0
    bcell_size_x = 16  # size of the region for printing
    bcell_size_y = 16
    bcell_size_z = 16
 
    # Biocellion optional parameteres
    bcell_input_param = PARAMETERS
    bcell_verbosity = 0  # [0-5]

    bcell_num_threads = 6
    bcell_num_node_groups = 1
    bcell_num_nodes_per_group = 1
    bcell_num_sockets_per_node = 1
    bcell_max_load_imbalance = 1.2

    bcell_super_x = 64
    bcell_super_y = 64
    bcell_super_z = 64

    bcell_summary = 1
    bcell_load_balance = 0
    bcell_regridding = 1000
    bcell_checkpoint = 0

    bcell_refine_ratio = 2
    bcell_fill_ratio = 0.5

    #  Write xml for Biocellion
    top = Element('biocellion')

    comment = Comment('Input parameters for  Biocellion, generated by Python parcer ')
    top.append(comment)

    # Printing Required parameterss
    xml_required = SubElement(top, 'required')
    xml_required.append(Comment('Required Parameters for biocellion.'))

    xml_time_step = SubElement(xml_required, 'time_step')
    xml_time_step.set('num_baseline', str(bcell_num_baseline))

    xml_domain = SubElement(xml_required, 'domain')
    xml_domain.set('x', str(bcell_nx))
    xml_domain.set('y', str(bcell_ny))
    xml_domain.set('z', str(bcell_nz))

    xml_init_data = SubElement(xml_required, 'init_data')
    xml_init_data.set('partition_size', str(bcell_partition_size))
    xml_init_data.set('src', "code")  # currently no imput from binary

    xml_output = SubElement(xml_required, 'output ')
    xml_output.set('path', bcell_path)
    xml_output.set('interval', str(bcell_interval))
    xml_output.set('particle', "pvtp")
    xml_output.set('grid', "vthb")
    xml_output.set('start_x', str(bcell_start_x))
    xml_output.set('start_y', str(bcell_start_y))
    xml_output.set('start_z', str(bcell_start_z))
    xml_output.set('size_x', str(bcell_size_x))
    xml_output.set('size_y', str(bcell_size_y))
    xml_output.set('size_z', str(bcell_size_z))

    # Printing Required parameterss
    xml_optional = SubElement(top, 'optional')
    xml_optional.append(Comment('optional Parameters for biocellion.'))

    xml_bioparm_model = SubElement(xml_optional, 'model')
    xml_bioparm_model.set('param', bcell_input_param)

    xml_bioparm_stdout = SubElement(xml_optional, 'stdout')
    xml_bioparm_stdout.set('verbosity', str(bcell_verbosity))

    xml_bioparm_system = SubElement(xml_optional, 'system')
    xml_bioparm_system.set('num_node_groups', str(bcell_num_node_groups))
    xml_bioparm_system.set('num_nodes_per_group', str(bcell_num_nodes_per_group))
    xml_bioparm_system.set('num_sockets_per_node', str(bcell_num_sockets_per_node))
    xml_bioparm_system.set('max_load_imbalance', str(bcell_max_load_imbalance))#
    xml_bioparm_system.set('num_threads', str(bcell_num_threads))

    xml_bioparm_super_partition = SubElement(xml_optional, 'super_partition')
    xml_bioparm_super_partition.set('x', str(bcell_super_x))
    xml_bioparm_super_partition.set('y', str(bcell_super_y))
    xml_bioparm_super_partition.set('z', str(bcell_super_z))

    xml_interval = SubElement(xml_optional, 'interval')
    xml_interval.set('summary', str(bcell_summary))
    xml_interval.set('load_balance', str(bcell_load_balance))
    xml_interval.set('regridding', str(bcell_regridding))
    xml_interval.set('checkpoint', str(bcell_checkpoint))

    xml_amr = SubElement(xml_optional, 'amr')
    xml_amr.set('refine_ratio', str(bcell_refine_ratio))
    xml_amr.set('fill_ratio', str(bcell_fill_ratio))

    xml_file.write(prettify(top))




