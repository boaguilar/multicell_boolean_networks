import sys
import os
import subprocess
import numpy
import shutil
import math
from scipy.stats import spearmanr
from subprocess import check_output
import xml.etree.ElementTree as ET
from xml.etree.ElementTree import Element, SubElement, Comment
from xml.dom import minidom
import csv

import BiocellionUtils as biocell


a_probmut = [0.0458, 0.1844, 0.3362, 0.5482, 0.6207, 0.7493, 0.9606 ]
Nprobpoints = len( a_probmut ) 

# important paths to run the Biocellion PDAC model
tbbpath="/users/baguilar/BIOCELLION_RELEASE/tbb2016_20161128oss/lib/intel64/gcc4.4"
biomodel="/users/baguilar/BiocellionModels/tissueblock_rbn_ssdiffusion"
biocellpath="/users/baguilar/BIOCELLION_RELEASE/biocellion/framework/main/biocellion.DP.SPAGENT.OPT"
ldpath= "LD_LIBRARY_PATH=$LD_LIBRARY_PATH:" + tbbpath + ":" + biomodel
MODEL_DIR= "/users/baguilar/biocellion_files_pccmut_psc_cd4_tampalma_cd8bolouri/"
SIMULATIONS_DIR= "/titan/cancerregulome14/users/mechlin/cellular_automata_diversity/boris_pdac/Perturbations2" 

#inputs
SAMPLE_ID = sys.argv[1]
RUNID = sys.argv[2]


mytuple = divmod( int(RUNID)-1 , Nprobpoints  )
INSTANCE  = str( mytuple[0] )
probi = mytuple[1] 

MUT_CELLID = -1
MUT_GENEID = [ 0 ]
MUT_PROBAB = [ 0.0 ] 


MUT_CELLID = int( sys.argv[21] )
MUT_GENEID[0] = int( sys.argv[22] )


# simultion parameters
SIMULATION_STEPS="400"
ANALYSIS_STEPS="200"
GAMMA = "0.005555555556"
RON = "5.0"
PHI_OFF = "0.00197212"
BOOLNETWORK = MODEL_DIR + "pccmut_psc_cd4_tam_cd8"
OUTPUT_DIR = SIMULATIONS_DIR + "/output" + SAMPLE_ID + "_" +INSTANCE + "_" + str(MUT_CELLID) + "_" + str(MUT_GENEID[0])   
BIOCELLION_OUTPUT_FILE =  OUTPUT_DIR  + '/biocellion_test.txt'
fractions_filename = MODEL_DIR + '/fractions_5cellmodel_tcga_july26.txt'
mutations_filename  = MODEL_DIR + '/MutationStates_TP53_CDKN2A_SMAD4_KRAS_july26.txt'
Lambda = 8.3556e-05  # density of cells
Lambda_max = 8.0 * Lambda  # maximum density
Lxyz     = 320
Ngenes = 44
OUTPUT_GENE_EXPRESSION  = range( Ngenes  )
MUTATIONS_STATES = [ 27, 0, 8, 1 ] # TP53, CDKN2A, SMAD4, KRAS
ALPHA_VALUES = [ 0.0, 0.0, 0.0, 0.0 ]

### Read parameteres
RHO_P = float(  sys.argv[2] )
KON_PCC = sys.argv[3]
KON_PSC = sys.argv[4]
KON_CD4 = sys.argv[5]
KON_TAM = sys.argv[6]
KON_CD8 = sys.argv[7]
RON_PCC_VEGF     = sys.argv[8]
RON_PCC_EGF      = sys.argv[9]
RON_PCC_bFGF     = sys.argv[10]
RON_PCC_PDGFBB   = sys.argv[11]
RON_PCC_TGFbeta1 = sys.argv[12]
RON_PSC = sys.argv[13]
RON_CD4 = sys.argv[14]
RON_TAM = sys.argv[15]
RON_CD8 = sys.argv[16]
ALPHA_VALUES[0] = float( sys.argv[17] )
ALPHA_VALUES[1] = float( sys.argv[18] )
ALPHA_VALUES[2] = float( sys.argv[19] )
ALPHA_VALUES[3] = float( sys.argv[20] )



#  Read cellular fractions                       
fractions = []
with open( fractions_filename , 'r'  ) as f:
   lines = f.readlines()
   fractions_str = lines[ int(SAMPLE_ID) ].strip().split()
   fractions_pre = [ float(x) for x in fractions_str ]
   sum_frac = sum( fractions_pre )
   fractions = [ x/sum_frac for x in fractions_pre  ]


if os.path.isdir( OUTPUT_DIR ) :
    pass 
else :

    try:
        os.mkdir( OUTPUT_DIR  )
    except OSError:
        print ("Creation of the directory %s failed" % OUTPUT_DIR  )
        sys.exit()

# probi in range( len(a_probmut) )  :
#for probi in range( 2 )  :

MUT_PROBAB[0] = a_probmut[ probi ]
    
#input files for simulations
XYZRTfile =  OUTPUT_DIR  + '/cell_positions.'+ str(probi) +'.xyzrt.txt'
biocell.GenerateXYZRTfiles( XYZRTfile, Lxyz, fractions, Lambda,  RHO_P , Lambda_max, 0.0 )
BOOLSTATES = OUTPUT_DIR  + '/bool_states_sample.'+ str(probi) +'.txt'
#biocell.add_mutations(  XYZRTfile , BOOLSTATES, MUTATIONS_STATES, ALPHA_VALUES )
biocell.add_mutations_pcc_stroma( XYZRTfile , BOOLSTATES, MUTATIONS_STATES, ALPHA_VALUES, MUT_CELLID, MUT_GENEID, MUT_PROBAB )

#Parameteres 
SecretionCANCER = RON_PCC_VEGF+' '+RON_PCC_EGF+' '+RON_PCC_bFGF+' '+RON_PCC_PDGFBB+' '+RON_PCC_TGFbeta1
SecretionSTROMA =             RON_PSC+' '+RON_CD4+' '+RON_TAM+' '+RON_CD8
ThresholdPARAM  = KON_PCC+' '+KON_PSC+' '+KON_CD4+' '+KON_TAM+' '+KON_CD8

#Create Biocellion input file 
parameter_str =GAMMA+' '+ PHI_OFF+' '+SecretionCANCER+' '+SecretionSTROMA+' '+ThresholdPARAM+' '+XYZRTfile+' '+BOOLNETWORK+' '+BOOLSTATES
xmlname = OUTPUT_DIR  + "/run."+ str(probi) +".xml"
biocell.write_bcell_xml( OUTPUT_DIR, parameter_str, xmlname, int( SIMULATION_STEPS )  )

#command to run biocellion
cmd = ldpath + " " + biocellpath + " " +  xmlname  +" > "+  OUTPUT_DIR  + "/output."+ str(probi) +".txt"
os.system( cmd  )



