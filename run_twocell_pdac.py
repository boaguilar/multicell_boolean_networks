import sys
import os
import subprocess
from subprocess import check_output
import PythonLib.BiocellionUtils as biocell


# important paths to run the Biocellion PDAC model
MBN_DIR = "/home/boris/multicell_boolean_networks" # change this the path in yout computer
tbbpath=  MBN_DIR + "/ThirdParty/tbb2018u3/lib/intel64/gcc4.4"
biomodel= MBN_DIR + "/BiocellionModel"
biocellpath= MBN_DIR + "/ThirdParty/biocellion1.2/framework/main/biocellion.DP.SPAGENT.OPT"
ldpath= "LD_LIBRARY_PATH=$LD_LIBRARY_PATH:" + tbbpath + ":" + biomodel
MODEL_DIR= MBN_DIR + "/Models/twocell_pdac"
SIMULATIONS_DIR= MBN_DIR + "/Models/twocell_pdac/sim_output"

 
#inputs
ParamFile =  MBN_DIR + "/Models/twocell_pdac/ParametersLHC_pccmut_psc_Lambda30_set1.txt"
PARAM_ID =  '0'  # Parameter ID ( row in ParamFile )
#PARAM_ID =  sys.argv[1]

# simultion parameters
NINSTANCES = 10
SIMULATION_STEPS="100"
ANALYSIS_STEPS="50"
GAMMA = "0.005555555556"
RON = "5.0"
PHI_OFF = "0.00197212"
BOOLNETWORK = MODEL_DIR + "/pccmut_psc"
OUTPUT_DIR = SIMULATIONS_DIR + "/output" + PARAM_ID
BIOCELLION_OUTPUT_FILE =  OUTPUT_DIR  + '/biocellion_test.txt'
Lambda = 8.3556e-05  # density of cells
Lambda_max = 8.0 * Lambda  # maximum density
Lxyz     = 320
NumGenes = 41  
OUTPUT_GENE_EXPRESSION  = range( NumGenes  )
MUTATIONS_STATES = [ 1 ] # KRAS
CYTONET_FILE = OUTPUT_DIR + "/cytokine_net.txt"

lines_params = []
with open( ParamFile, 'r') as f:
    lines_params = f.readlines()
parms = lines_params[ int( PARAM_ID  )  ].strip().split()


### Read parameteres from the file
FSTROMA = float( parms[0] )

#cytokine network: 0 
CYTOKINE_NET = """R 1 0 2 {6}
R 2 0 3 {6}
R 4 0 4 {6}
R 0 1 3 {7}
R 1 1 4 {7}
R 2 1 5 {7}
R 3 1 6 {7}
R 4 1 7 {7}
S 0 0 30 {0}
S 1 0 31 {1}
S 2 0 32 {2}
S 3 0 33 {3}
S 4 0 34 {4}
S 0 1 24 {5}
S 2 1 25 {5}
S 3 1 26 {5}
S 4 1 27 {5}
""".format(parms[1],parms[2],parms[3],parms[4],parms[5],parms[6],parms[7],parms[8])

Ncues = 5 # number of cytokines
RHO_P = float(  parms[9] ) # 
ALPHA = float( parms[10] )
F_R =  float( parms[11] )

Lambda_max   = 8.0 * Lambda
fractions    = [ 1.0 - FSTROMA, FSTROMA ]
MUTATIONS_STATES  = [ 0, 1 ]
ALPHA_VALUES  = [ 1.01, ALPHA ]

try:
    if not os.path.isdir(OUTPUT_DIR) :
        os.mkdir( OUTPUT_DIR  )
except OSError:
    print ("Creation of the directory %s failed" % OUTPUT_DIR  )
    sys.exit()

with open( CYTONET_FILE, 'w' ) as f :
    f.write( CYTOKINE_NET )  


for instance in range(NINSTANCES) :

    XYZRTfile =  OUTPUT_DIR  + '/cellpositions_'+ str(instance) +'.txt'
    biocell.GenerateXYZRTfiles( XYZRTfile, Lxyz, fractions, Lambda,  RHO_P , Lambda_max, 0.0 )

    BOOLSTATES = OUTPUT_DIR  + '/boolstates_'+ str(instance)  +'.txt'
    biocell.add_mutations_pccmut_psc(  XYZRTfile , BOOLSTATES, NumGenes, MUTATIONS_STATES,  ALPHA_VALUES )

    output_name = OUTPUT_DIR  + "/output_" + str(instance)  + ".txt"

    param_xml = GAMMA+' '+PHI_OFF+' '+str(Ncues)+' '+BOOLNETWORK+' '+CYTONET_FILE+' '+XYZRTfile+' '+BOOLSTATES
    xmlname = OUTPUT_DIR  + "/run_"+ str(instance)  + ".xml"
    biocell.write_bcell_xml( OUTPUT_DIR, param_xml, xmlname, int( SIMULATION_STEPS )  )

    #command to run biocellion 
    cmd = ldpath + " " + biocellpath + " " +  xmlname  +" > "+  output_name
    os.system( cmd  )

    # print gene expression of cancer cells
    cellid = 0 # change it to 1 for stellate cells
    Ncells_cancer = int( biocell.NumCellsFromXYZR ( XYZRTfile, cellid ) )
    if ( Ncells_cancer > 0 ) :

        gexpression_file = OUTPUT_DIR + "/gene_expression_instance"+ str(instance) + "_BN_"+ str(cellid) +".txt"

        xx = biocell.GetExpTrajectoriesFromOutput('BN_'+ str(cellid),output_name,NumGenes)
            
        with open( gexpression_file , 'w' ) as outfile :
            for x in xx :
                gene_expresion =  ["{0:9.6f}".format( float(count)/float(Ncells_cancer)) for count in x ]            
                outfile.write( "".join(gene_expresion) + "\n" )


