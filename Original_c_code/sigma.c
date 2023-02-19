float sigma(float cecita1,float cecita2,float complessita,
float rifiuto_effettivo,float disis_espressa,float disis_ricevuta)
{
	float tensione0,tensione1,tensione2,tensione,lavoro;
	float coef,diff,diff1;
	float stima,cieco,compl,rifef,disis,ripre;
	cieco=(cecita1+cecita2)/2;compl=complessita;
	rifef=rifiuto_effettivo;
	ripre=disis_espressa;disis=disis_ricevuta;
	tensione0 = cieco + compl;
	diff = compl - cieco;
	diff1 = cieco - compl;
	coef = 1;
	if (compl > cieco)
		coef=1-pow(1+pow((1-pow(diff,2))/diff,2),-1);
	if (compl > cieco)
		coef=1-pow(1+pow((1-pow(diff1,4))/pow(diff,2),2),-1);
	tensione0 = tensione0 * coef;
	diff = ripre - cieco;
	diff1 = cieco - ripre;
	coef = 1;
	if (ripre > cieco)
		coef=1-pow(1+pow((1-pow(diff,2))/diff,2),-1);
	if (ripre > cieco)
		coef=1-pow(1+pow((1-pow(diff1,4))/pow(diff,2),2),-1);
	tensione1 = ripre * coef;
	tensione =(tensione0+pow(tensione1,2))-(tensione0*pow(tensione1,2));
	stima = pow(disis,2) * pow(ripre,2);
	tensione2 = stima +pow(rifef,2);
	lavoro= (tensione + tensione2);
return(lavoro);
}