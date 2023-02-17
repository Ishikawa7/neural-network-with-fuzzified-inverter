### C CODE

#float sigma(int pat)
#{
#	float tensione0,tensione1,tensione2,tensione,lavoro;
#	float coef,diff,diff1;
#	float stima,cieco,compl,rifef,disis,ripre;
#	
#   cieco=(punti[pat][1]+punti[pat][2])/20;
#	compl=punti[pat][15]/10;
#   rifef=punti[pat][3]/10;
#	ripre=punti[pat][4]/10;
#   disis=punti[pat][5]/10;
#
#	tensione0 = cieco + compl;
#	diff = compl - cieco;
#	diff1 = cieco - compl;
#	coef = 1;

#	if (compl > cieco)
#		coef=1-pow(1+pow((1-pow(diff,2))/diff,2),-1);
#	if (compl < cieco)
#		coef=1-pow(1+pow((1-pow(diff1,4))/pow(diff,2),2),-1);

#	tensione0 = tensione0 * coef;
#	diff = ripre - cieco;
#	diff1 = cieco - ripre;
#	coef = 1;

#	if (ripre > cieco)
#		coef=1-pow(1+pow((1-pow(diff,2))/sqrt(pow(diff,2)),2),-1);
#	if (ripre < cieco)
#		coef=1-pow(1+pow((1-pow(diff1,4))/sqrt(pow(diff,4)),2),-1);

#	tensione1 = ripre * coef;
#	tensione =(tensione0+pow(tensione1,2))-(tensione0*pow(tensione1,2));
#	stima = pow(disis,2) * pow(ripre,2);
#	tensione2 = stima +pow(rifef,2);
#	lavoro= (tensione + tensione2)*100;
#   return(lavoro);
#}

# import sqrt function
from math import sqrt

## CHANGES IN VARIABLES NAMES

#cieco = cecita (OK)
#compl = complessita (OK)
#rifef = rifiuto_effettivo (OK)
#ripre = dististima_espressa (OK)
#disis = disistima_ricevuta (OK)

# SIGMA EQUATION BOOK
def sigma_equation_book(cecita, complessita, disistima_espressa, disistima_ricevuta, rifiuto_effettivo):
    coef0 = 1
    coef1 = 1

    tensione0 = cecita + complessita #cieco nel libro
    diff0 = abs(complessita - cecita)
    if complessita > cecita:
        coef0 = 1 - (1 + ( (1 - diff0**2) / diff0 )**2 )**(-1)
    if complessita < cecita:
        coef0 = 1 - (1 + ( (1 - diff0**4) / (diff0)**2 )**2 )**(-1)
    
    tensione0 = tensione0 * coef0

    diff1 = abs(disistima_espressa - tensione0)
    if disistima_espressa > tensione0:
        coef1 = 1 - (1 + ( (1-diff1**2) / diff1 )**2 )**(-1)
    if disistima_espressa < tensione0:
        coef1 = 1 - (1 + ( (1-diff1**4) / (diff1)**2 )**2 )**(-1)
    tensione1 = disistima_espressa * coef1

    tensione = (tensione0 + tensione1**2) - (tensione0 * tensione1**2)
    stima = disistima_espressa**2 * disistima_ricevuta**2
    tensione2 = stima + (rifiuto_effettivo)**2
    LAVORO = (tensione + tensione2) * 100
    return LAVORO

# SIGMA EQUATION C CODE
# comments highligts the differences between the book and the c code
def sigma_equation_c_code(cecita, complessita, disistima_espressa, disistima_ricevuta, rifiuto_effettivo):
    tensione0 = cecita + complessita
    diff = complessita - cecita #valore assoluto e una sola differenza
    diff1 = cecita - complessita
    coef = 1
    if complessita > cecita:
        coef = 1 - (1 + (1 - (diff ** 2))/diff ** 2) ** -1 #quadrato su diff
    if complessita < cecita:
        coef = 1 - (1 + (1 - (diff1 ** 4))/(diff ** 2) ** 2) ** -1
    tensione0 = tensione0 * coef

    diff = disistima_espressa - cecita #valore assoluto e una sola differenza
    diff1 = cecita - disistima_espressa # disistima espressa - cecita in vece che - tensione0
    coef = 1
    if disistima_espressa > cecita:
        coef = 1 - (1 + (1 - (diff ** 2))/sqrt(diff ** 2)) ** -1 #quadrato su diff e radice quadrata
    if disistima_espressa < cecita:
        coef = 1 - (1 + (1 - (diff1 ** 4))/sqrt(diff ** 4)) ** -1 #elevamento alla quarta invece che quadrato e radice quadrata
    tensione1 = disistima_espressa * coef

    tensione = (tensione0 + tensione1 ** 2) - (tensione0 * tensione1 ** 2)
    stima = disistima_ricevuta ** 2 * disistima_espressa ** 2
    tensione2 = stima + rifiuto_effettivo ** 2
    LAVORO = (tensione + tensione2) * 100
    return LAVORO
