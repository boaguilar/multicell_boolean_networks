import sys
import os
import subprocess
import numpy
import shutil
import math
from scipy.stats import spearmanr
from subprocess import check_output
import PythonLib.BiocellionUtils as biocell

a_probmut = [0.0458, 0.1844, 0.3362, 0.5482, 0.6207, 0.7493, 0.9606 ]
Nprobpoints = len( a_probmut ) 

# important paths to run the Biocellion PDAC model
MBN_DIR = "/home/boris/GITHUB/multicell_boolean_networks" # change this the path in yout computer
tbbpath=  MBN_DIR + "/ThirdParty/tbb2018u3/lib/intel64/gcc4.4"
biomodel= MBN_DIR + "/BiocellionModel"
biocellpath= MBN_DIR + "/ThirdParty/biocellion1.2/framework/main/biocellion.DP.SPAGENT.OPT"
ldpath= "LD_LIBRARY_PATH=$LD_LIBRARY_PATH:" + tbbpath + ":" + biomodel
MODEL_DIR= MBN_DIR + "/Models/fivecell_pdac"
SIMULATIONS_DIR= MBN_DIR + "/Models/fivecell_pdac/sim_output"

#inputs
SAMPLE_ID = sys.argv[1]
MUT_CELLID = -1        # ID of cell that will be peturbed -1 for no perturbation
MUT_GENEID = [ 0 ]     # ID of the gene that will be perturbed
MUT_PROBAB = [ 0.0 ]   # Mutation probability. 

# constant parameters
NINSTANCES = 1 
SIMULATION_STEPS="400"
ANALYSIS_STEPS="200"
GAMMA = "0.005555555556"
RON = "5.0"
PHI_OFF = "0.00197212"
BOOLNETWORK = MODEL_DIR + "/pccmut_psc_cd4_tam_cd8"
OUTPUT_DIR = SIMULATIONS_DIR + "/output" + SAMPLE_ID    
BIOCELLION_OUTPUT_FILE =  OUTPUT_DIR  + '/biocellion_test.txt'
fractions_filename = MODEL_DIR + '/fractions_5cellmodel_tcga_july26.txt'
mutations_filename  = MODEL_DIR + '/MutationStates_TP53_CDKN2A_SMAD4_KRAS_july26.txt'
CYTONET_FILE = OUTPUT_DIR + '/cytokine_net.txt'
parameter_file = MODEL_DIR + '/OptimumParameteres_May7.txt'
Lambda = 8.3556e-05  # density of cells
Lambda_max = 8.0 * Lambda  # maximum density
Lxyz     = 320
Ngenes = 44
Ncues = 16
OUTPUT_GENE_EXPRESSION  = range( Ngenes  )
MUTATIONS_STATES = [ 27, 0, 8, 1 ] # TP53, CDKN2A, SMAD4, KRAS
ALPHA_VALUES = [ 0.0, 0.0, 0.0, 0.0 ]

# Read Optimum parameteres
params = []
with open( parameter_file,'r') as f :
     all_lines   = f.readlines( )
     params = all_lines[ int( SAMPLE_ID)].strip().split() 

RHO_P = float(  params[0] )
ALPHA_VALUES[0] = float( params[15] )
ALPHA_VALUES[1] = float( params[16] )
ALPHA_VALUES[2] = float( params[17] )
ALPHA_VALUES[3] = float( params[18] )

# try to create oputput directory
try:
    if not os.path.isdir(OUTPUT_DIR) :
        os.mkdir( OUTPUT_DIR  )
except OSError:
    print ("Creation of the directory %s failed" % OUTPUT_DIR  )
    sys.exit()


#  Create cytokine network
THRESHOLDS = [ params[1], params[2], params[3], params[4], params[5] ]
CANCER_RON = [ params[6], params[7], params[8], params[9], params[10] ]
CELLS_RON = [ '1.0' , params[11], params[12], params[13], params[14] ]
biocell.CytokineNet_fivecell(CYTONET_FILE, THRESHOLDS, CANCER_RON, CELLS_RON ) 


#  Read cellular fractions                       
fractions = []
with open( fractions_filename , 'r'  ) as f:
   lines = f.readlines()
   fractions_str = lines[ int(SAMPLE_ID) ].strip().split()
   fractions_pre = [ float(x) for x in fractions_str ]
   sum_frac = sum( fractions_pre )
   fractions = [ x/sum_frac for x in fractions_pre  ]


for instance in range(NINSTANCES) :

    XYZRTfile =  OUTPUT_DIR  + '/cellpositions_'+ str(instance) +'.txt'
    biocell.GenerateXYZRTfiles( XYZRTfile, Lxyz, fractions, Lambda,  RHO_P , Lambda_max, 0.0 )

    BOOLSTATES = OUTPUT_DIR  + '/boolstates_'+ str(instance)  +'.txt'
    biocell.add_mutations_pcc_stroma( XYZRTfile , BOOLSTATES, MUTATIONS_STATES, ALPHA_VALUES, MUT_CELLID, MUT_GENEID, MUT_PROBAB )

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

        xx = biocell.GetExpTrajectoriesFromOutput('BN_'+ str(cellid),output_name, Ngenes )

        with open( gexpression_file , 'w' ) as outfile :
            for x in xx :
                gene_expresion =  ["{0:9.6f}".format( float(count)/float(Ncells_cancer)) for count in x ]
                outfile.write( "".join(gene_expresion) + "\n" )

