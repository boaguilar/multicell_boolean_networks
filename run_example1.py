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
import PythonLib.BiocellionUtils as biocell

# important paths to run the Biocellion PDAC model
MBN_DIR = "/home/boris/multicell_boolean_networks" # change this path in your computer

tbbpath=  MBN_DIR + "/ThirdParty/tbb2018u3/lib/intel64/gcc4.4"
biomodel= MBN_DIR + "/BiocellionModel"
biocellpath= MBN_DIR + "/ThirdParty/biocellion1.2/framework/main/biocellion.DP.SPAGENT.OPT"
ldpath= "LD_LIBRARY_PATH=$LD_LIBRARY_PATH:" + tbbpath + ":" + biomodel
MODEL_DIR= MBN_DIR + "/Models/example1"
SIMULATIONS_DIR= MBN_DIR + "/Models/example1/sim_output" 

# simultion parameters
SIMULATION_STEPS="40"
GAMMA = "0.005555555556"
PHI_OFF = "0.00197212"
BOOLNETWORK = MODEL_DIR + "/example1"   
CYTOKNETWORK = MODEL_DIR + "/example1_cytonet.txt"
BIOCELLION_OUTPUT_FILE = SIMULATIONS_DIR + '/biocellion_output.txt'
Lambda = 8.3556e-05   # density of cells
Lxyz     = 320              # length of the regular simulations domain
Ngenes = 4                  # number of genes of the largest BN 
Ncytokines = 2  
a_fractions = [0.5, 0.5]    # fractions of cell 0 and cell 1 respectively. 


# Generate positions for the two cell types with Poisson distribution
XYZRTfile = SIMULATIONS_DIR  + '/cell_positions.xyzrt.txt'
positions = biocell.PoissonPP( Lambda, Lxyz, 3 ) 
types = biocell.UniformCellTypes( len(positions) , [0, 1] , a_fractions )
biocell.PrintXYZRTfromPoints( XYZRTfile, positions , types ) 

# generate initial states of the boolean network
BOOLSTATES = SIMULATIONS_DIR + '/bool_states.txt'
biocell.GenerateInitialBNs( XYZRTfile , BOOLSTATES, Ngenes )

#Create Biocellion input file 
parameter_str = GAMMA+' '+ PHI_OFF+' '+ str(Ncytokines)+' '+BOOLNETWORK+' '+CYTOKNETWORK+' '+ XYZRTfile + ' ' + BOOLSTATES
xmlname = SIMULATIONS_DIR + "/run.xml"
biocell.write_bcell_xml( SIMULATIONS_DIR, parameter_str, xmlname, int( SIMULATION_STEPS )  )

#command to run biocellion
cmd = ldpath + " " + biocellpath + " " +  xmlname  +" > "+ BIOCELLION_OUTPUT_FILE 
os.system( cmd  )

#print percentage of cells with activated receptor 0, see Docs directory for more details of the model
receptor0_ON = []  
with open(  BIOCELLION_OUTPUT_FILE, 'r') as f:
    for line in f : 
        if ( 'BN_0_0' in line ) :  
            columns =  line.strip().split(':') 
            receptor0_ON.append( float( columns[-1] ) ) 
                    
        elif ( 'BN_1_0' in line ) :  
            columns =  line.strip().split(':') 
            receptor0_ON[-1] += ( float( columns[-1] ) ) 

TNcells = len(positions )             
for ncells in receptor0_ON : 
    print( ncells / TNcells ) 



