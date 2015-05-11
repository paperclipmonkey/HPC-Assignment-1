/* authors Dominic chim & Michael Waterworth
HPC Assignment 1 C Part */

/*
Why we switch between old_u and new_u
Alternate between these two calls switching the old_u and new_u parameters.
This allows reuse of the objects switching over which one to read from and which to write to - Saves resources with little copying
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Assignment1C++.h"

//set dimensions of array
struct Params
{
	double cx,cy;  //Propogation variable in X & Y
	int nts; // total number of timesteps to be computed
}params;


int main(int argc, char *argv[])
{
    //./temp_dist2D 0.1 0.1 50 initial_data.csv

    /* Read in grid sampling paameters and timesteps and initialize struct Params */
	struct Params para;
	para.cx=strtod(argv[1],NULL);
	para.cy=strtod(argv[2], NULL);
	para.nts=strtod(argv[3], NULL);

	/* Read grid dimension dim and allocate old_u and new_u */
    printf("Using [%d][%d] grid.\n", XDIM, YDIM);
	double old_u[XDIM][YDIM];
    double new_u[XDIM][YDIM];

    int it = 0; // Ts iterator
    char *fname= argv[4];
    char nname[] = "final_data_";
    
    printf("Starting serial version of 2D temperature distribution example...\n");
 
    /* Initialize grid from input file */
    printf("Initializing grid from input file: %s\n",fname);
    initdata(old_u, fname);

    // Iterate over all timesteps and create output files
    printf("Iterating over %d time steps...\n", para.nts);
    while(it < para.nts){
        it++;//Increment iterator first - start at one
        if(it % 2 == 0){//if timestep is odd 
            update(para.cx, para.cy, old_u, new_u);
			prtdata(XDIM, YDIM, it, *old_u, nname);//Save intermediate timesteps
        } else {// if timestep is even 
            update(para.cx, para.cy, new_u, old_u);
			prtdata(XDIM, YDIM, it, *new_u, nname);//Save intermediate timesteps
        }
    }
    printf("Done. Created output file: %d\n", it);

	getchar();
	return 0;
}
 


