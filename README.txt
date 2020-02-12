Multicellular Boolean Networks 
==============================

Description 
===========
Perform simulations of a multicellular system in which each cell is characterized 
by a Boolean Network, and cell-cell communication is mediated by a diffusion of 
cytokines secreted by cells. Cells read the cytokines concentration to determine 
the Boolean state of the corresponding cytokine receptors.  From user defined
initial Boolean states of cells and model parameters the simulations outputs the 
average concentration of every gene for each of the cell types of PDAC model.

More details:
B. Aguilar, D.L. Gibbs, D.L. Reiss, M. McConnell, S.A. Danziger, A. Dervan,
M. Trotter, D. Bassett, R. Hershberg, A.V. Ratushny, and I. Shmulevich,
"A generalizable data-driven multicellular model of pancreatic ductal adenocarcinoma",
submmited to GigaScience.


Requeriments
============
1) Biocellion1.2. You can download Biocellion from https://biocellion.com and read 
   installation steps from the Manual. 
   Biocellion1.2 binary is included in the "biocellion1.2".
2) Python 3. Used to generate the files necessary to run simulations.
3) Threading Building Blocks library ( http://threadingbuildingblocks.org ).
   There is one version of this library in the "ThirdParty" direactory.


Model compilation
=================
The multicellular Boolean network model is implemented in Biocelliion1.2. To compile
the model follow the following steps: 

1) Update the variable name "BIOCELLION_ROOT" in the file "Makefile.model" in the
   "BiocellionModel" directory,  to the "biocellion1.2" directory in your computer.
2) Go to the directory "BiocellionModel" then do "make clean"  and "make".

Usage
=====
Please check the file "Models/example1/Models/example1/Two_cell_model_specification.pdf" 
for details about how to specify the Boolean networks for each cell type and
the cytokine network.
The following commands are used two run the implemented models:

1) To run the two-cell example model update the appropiate paths in the the script 
   "run_example1.py". Some details of the two cell model and its input format 
   are available in user_guid.pdf file. 
   A simulation of this example can be perofrmed by the following commands:

   python run_example1.py

2) To run the pdac model for cancer and stellate cell (two cell pdac model) 
   run the following command :

   python run_twocell_pdac.py 

3) The five cell model of Pancreatic cancer is implemented in the script 
   run_fivecell_pdacsample.py. This script allos you to run a simulation 
   of a TCGA sample spacified by the user. Moreover a user can setup a 
   perturbation if requerided. A simulation can be perofrmed by the 
   following command:

   python run_fivecell_pdacsample.py  $SAMPLE_ID 
  
   where $SAMPLE_ID is a number from 0-118 that represents the ID 
   of the TCGa sample.


Description of additional modeling Files 
========================================

- Models/example1/example1.* :  Files of Boolean network of the two cell toy model
  A description of the BN format is included in the file Doc/Docs/Two_cell_model_specification.pdf
- Models/example1/example1_cytonet.txt : cytokine newtork file for the two cell toy model
- Models/example1/Models/example1/Two_cell_model_specification.pdf : Details about model specification for the two cell toy model

- Models/twocell_pdac/pccmut_psc.* : Files of Boolean network of the two cell pdac model 
  These Boolean networks adapted from Tables S3 and S4 of Aguilar et al. (Supporting Material). 
- Models/twocell_pdac/ParametersLHC_pccmut_psc_Lambda30_set1.txt : Latin Hypercube parameters for the two cell pdac model

- Models/fivecell_pdac/TCGA_barcodes_paad.txt : List of 119 barcodes that identify the TCGA PAAD samples used in the work
- Models/fivecell_pdac/fractions_5cellmodel_tcga.txt :  Cellular fractions for each TCGA PAAD sample
- Models/fivecell_pdac/MutationStates_TCGA_CancerCells.txt : Presence (1) or absence (0) of mutation in TP53, CDKN2A, SMAD4, or KRAS in each TCGA PAAD sample
- Models/fivecell_pdac/paad_demix_tumor_geneexpression.tsv : Gene expression of cancer cells obtained by DeMix
- Models/fivecell_pdac/pccmut_psc_cd4_tam_cd8.* : Files of Boolean network of the five cell model of PDAC.
  These Boolean networks adapted from Tables S3, S4, S5, S6, and S7 of the Supporting Material of Aguilar et al.
  A description of the BN format is included in the file Doc/Docs/Two_cell_model_specification.pdf 
- Models/fivecell_pdac/OptimumParameteres_May7.txt : Optimum model parameters for each TCGA sample


Support
=======
Boris Aguilar : boris.aguilar@systemsbiology.org - model building and simulations
David Gibbs : david.gibbs@systemsbiology.org - methods to integrate TCGA data 
Alexander Ratushny : aratushny@celgene.com - Project leader
Ilya Shmulevich : ilya.shmulevich@systemsbiology.org - Project leader

