float ai[151][17],target[151][16];
float w_i_h[16][17],w_h_o[16][16];
float ah[16],ao[16];
float delta_hidden[16],delta_out[16],cm;
int numinput=15,numhidden=15,numoutput=15;
float rate,error,global_error;int pat=1;
float errore_dim[16];
int ruota=0;
float bias_h[16],bias_o[16];
float erroreloc[151][16],errorelista[151];
int bip=0;

int rate=1;

/* correggi pesi */
correggi_pesi(void)
{
	register int i,j;float somma_error;

	for (i=1;i<=numoutput;i++)
	{
		cm=target[pat][i]-ao[i];
		delta_out[i]=(delta_out[i]*cm)+cm*ao[i]*(1-ao[i]);
		bias_o[i]+=rate*delta_out[i];
		if(bip==1 && ruota==1)
			erroreloc[pat][i]=fabs(cm)*100;
		if(ruota==1) { error+=fabs(cm);
			       errore_dim[i]+=fabs(cm)*100;}
	}

	for (i=1;i<=numhidden;i++)
	{
		somma_error=0;
		for (j=1;j<=numoutput;j++)
			somma_error+=delta_out[j]*w_h_o[j][i];
		delta_hidden[i]=(ah[i]*(1-ah[i]))*somma_error;
		bias_h[i]+=rate*delta_hidden[i];
	}

// aggiornamenti pesi
	for(i=1;i<=numoutput;i++)
	{
		for (j=1;j<=numhidden;j++)
			w_h_o[i][j]+=rate*delta_out[i]*ah[j];
	}

	if(bip==1 && ruota==1) errorelista[pat]=error;

	for (i=1;i<=numhidden;i++)
	{
		for(j=1;j<=numinput;j++)
			w_i_h[i][j]+=rate*delta_hidden[i]*ai[pat][j];
	}
return(0);
}