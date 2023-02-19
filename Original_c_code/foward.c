#define NEPER 2.718281828459
int numinput=15,numhidden=15,numoutput=15;
float w_i_h[16][17],w_h_o[16][16];
float bias_h[16],bias_o[16];
float ah[16],ao[16];
int bip=0;
float ai[151][17]; // ai is the input of the network
float aoprima[151][16]; // aoprima stores the outputs of the network
int ruota=0;
int pat=1;

calcola(void)
{
	register int i,j;
	float net;
	for (i=1;i<=numhidden;i++)
	{
		net=0;
		for (j=1;j<=numinput;j++)
			net+=ai[pat][j]*w_i_h[i][j];
		if(net>99) net=99;
        if(net<-99) net=-99;
		ah[i]=1/(1+ pow(NEPER,-(net+bias_h[i])));

	}

	for (i=1;i<=numoutput;i++)
	{
		net=0;
		for (j=1;j<=numhidden;j++)
			net+=ah[j]*w_h_o[i][j];
		if(net>99) net=99;
        if(net<-99) net=-99;
		ao[i]=1/(1+ pow(NEPER,-(net+bias_o[i])));
		if(bip==1 && ruota==1)
			aoprima[pat][i]=ao[i]; 
	}
return(0);
}