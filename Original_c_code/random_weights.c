#include <stdlib.h>
#define frand() ((double) rand()/(RAND_MAX)) // random number between 0 and 1
int numinput=15,numhidden=15,numoutput=15;
float w_i_h[16][17],w_h_o[16][16];

pesi(void)
{
	int i,j;
	randomize();
	for(i=1;i<=numhidden;i++)
	{
		for(j=1;j<=numinput;j++)
			w_i_h[i][j]=frand()*.5; // random number between 0 and .5
	}

	for(i=1;i<=numoutput;i++)
	{
		for(j=1;j<=numhidden;j++)
			w_h_o[i][j]=frand()*.5;
	}
return(0);
}

// bias initialization to zero //