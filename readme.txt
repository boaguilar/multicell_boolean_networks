The model requires 5 parameters as before. 
To setup two BNs, one has to write the two nv vectors in a single file(*.nv). Each BN will occupy a line.
Similarly the varf of each BN should be placed one after another in a single file (*.varf)  


Memory is allocated to pass information to all mpi processes
1) Memory for all Voxels 
2) Memory for all Cells positions, radius, and type 
3) Memory for initial Boolean states of cells, This is variable 
4) Memory for definition of N Boolean network 
   each Boolean network needs the following space
   - 3 spaces of S32 for num_nodes, num_varf_rows, num_tt_rows.
   - a block of num_nodes*num_varf_rows*sizeof(S32)
   - a block of num_nodes*num_tt_rows*sizeof(S32)



