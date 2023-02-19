/* RETE FORWARD CON INVERTITORE SFUMATO */
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <bios.h>
#include <time.h>
#include <graphics.h>
extern unsigned _stklen=640000U;
#define NEPER 2.718281828459
#define frand() ((double) rand()/(RAND_MAX))
int finestra (int xdestra, int xsinistra, int yalto,int ybasso, int sfondo, int bordi);
int box(int max,int ascissa,int ordinata,int limite,int totale,int sfondo,int bordi,int barre);
quadro_ana(void);
apri_file(int num_file,unsigned long num);
rete_ana(unsigned long num);
scrivi_error(FILE *grafic);
quadro_rete();
rete_grafica(unsigned long conta);
ctr_file(void);
etichette_graf(void);
salva_dati(unsigned long epoca);
salva_testo(unsigned long epoca);
unsigned long prendi_dati(void);
long filesize(FILE *questio);
graf_error(unsigned long num);
tavola(unsigned long num);
etichette();azzera(void);
quadro_pesi(void);
scrivi(unsigned long num);
quadro(void);
grafo(long unsigned);
graf_pesi(long unsigned);
grafmode(void);
cambia(void);
fermo();
ctr(unsigned long num);
carica_dati(void);
risposte(char att[]);
pesi(void);
calcola(void);
correggi_pesi(void);
cornice(char titolo[]);
float sigma(float cecita1,float cecita2,float complessita,
float rifiuto_effettivo,float disis_espressa,float disis_ricevuta);
int driver,mode;
int natt,ncreo,nmod,ent,enp,pattern;
char creodi[10][40],modali[10][40],attori[10][10],operator[51][21];
float ai[151][17],target[151][16];
char dim[15][5]={"TrRi","RiTr"," Plu","TTra","TTrb"," Tr ","MeTr",
		 "MoTr","RiRi","MoFo","MMof","MoRi","MeRi"," Ri ","Comp"};

float w_i_h[16][17],w_h_o[16][16];
float ah[16],ao[16];
float delta_hidden[16],delta_out[16],cm;
int numinput=15,numhidden=15,numoutput=15;
float rate,error,global_error;int turni,pat=1;
float errore_dim[16];
int gra=1;char key;int ruota=0,b=0;
char att[10];
float bias_h[16],bias_o[16];
float aoprima[151][16],erroreloc[151][16],errorelista[151];
int bip=0;int pronto=0;
int ascissa,ordinata,limite,totale,sfondo,bordi,barre;
int xdestra,xsinistra,yalto,ybasso,max;
int saltalo=0,num_file,record;
FILE*grafic;

main()
{
	int sc,y;
	int i,j,mem;
	long int unsigned num=0;
	long int unsigned inizio=0;
	char t[10],r[10],value[20];
	char carattere;
	char titolo[31]=" RETE FORWARD CON INVERTITORE ";
	record=0;
	scegli:
	carica_dati();
	textcolor(1);textbackground(15);
	clrscr();cornice(titolo);
	textcolor(1);textbackground(15);
	ascissa=32;ordinata=5;totale=natt;limite=ordinata+natt;max=natt;
	xdestra = 30; xsinistra = 50; yalto = ordinata; ybasso =limite+1;
	sfondo=1;bordi=14;barre=4;
	finestra(xdestra,xsinistra,yalto,ybasso,sfondo,bordi);
	sc=box(max,ascissa,ordinata,limite,totale,sfondo,bordi,barre);
	if(sc==0) return(0);saltalo=sc-1;
	strcpy(att,attori[sc-1]);

	turnazione:
	textcolor(14);textbackground(1);
	for(j=1;j<=50;j++)
		{itoa(j,value,10);
		strcpy(operator[j]," ");
		strcat(operator[j],value);
		if(j<10) strcat(operator[j]," ");}

	ascissa=43;ordinata=15;totale=50;limite=ordinata+1;max=1;
	xdestra = 33; xsinistra = 47; yalto = ordinata; ybasso =limite+1;
	sfondo=1;bordi=14;barre=4;
	finestra(xdestra,xsinistra,yalto,ybasso,sfondo,bordi);
	gotoxy(35,16);cprintf(" TURNI :");
	turni=box(max,ascissa,ordinata,limite,totale,sfondo,bordi,barre);
	if(turni==0) goto scegli;

	textcolor(14);textbackground(1);
	strcpy(operator[1],"SI");strcpy(operator[2],"NO");
	ascissa=45;ordinata=19;totale=2;limite=ordinata+1;max=1;
	xdestra = 33; xsinistra = 47; yalto = ordinata; ybasso =limite+1;
	sfondo=1;bordi=14;barre=4;
	finestra(xdestra,xsinistra,yalto,ybasso,sfondo,bordi);
	gotoxy(35,20);cprintf(" CONFERMI:");
	carattere=box(max,ascissa,ordinata,limite,totale,sfondo,bordi,barre);
	if(carattere==0) goto turnazione;
	if(carattere==2)  goto scegli;

	rate=1;
	risposte(att);
	mem=ctr_file();
	if(mem==-1) goto turnazione;
	if (mem==0)
	{
		pesi();
		for(i=1;i<=numoutput;i++)
			bias_o[i]=delta_out[i]=0;
		for(i=1;i<=numhidden;i++)
			bias_h[i]=0;
		inizio=0;
	}
	if(mem==1) inizio=prendi_dati();

	num_file=1+(long)((long)((float)inizio/(float)pattern)/3968);
	textcolor(15);textbackground(1);clrscr();
	gra=1;etichette();azzera();key=0;

	for(num=inizio;key!=27;num++)
	{
	error=0;
	ruota++;
	calcola();
	correggi_pesi();
	global_error+=error;
	if(ruota==1 && pat==pattern) global_error/=pattern;
	if(ruota==1 && record<3968 && pat==pattern && num_file<=99)
	{       if(record==0) apri_file(num_file,num);
		record++;scrivi_error(grafic);
		if (record==3968) 
			{ printf("\a");fclose(grafic);record=0;num_file++;}
	}
	if (gra==1 && ruota==1 && pat==pattern) scrivi(num);
	else if (gra==0) grafo(num);
	else if (gra==2 && ruota==1 && pat==pattern) graf_pesi(num);
	else if (gra==4 && ruota==1 && pat==pattern) graf_error(num);
	else if (gra==5 && ruota==1) rete_grafica(num);
	else if (gra==6 && ruota==1) rete_ana(num);
	if (pat==pattern && ruota==1) azzera();
	ctr(num);
	if(record<3968 && key==27) fclose(grafic);
	}
	if(gra==0||gra>1) {closegraph();textmode(80);}

return(0);
}



carica_dati(void)
{
	FILE *dati;
	char v1[40];char v[7][5];char carattere;
	char valore[10],fine[21];
	int i,k,j;int long num;
	int m,cont,colonna,num1,num2,num3,num4;
	int riga,posatt,cont2;
	int p1,p2,p3,p4;
	k=0;j=0;
	dati=fopen("dati","rb");
	num=filesize(dati);
	if(num<=0) {fclose(dati);exit(0);}
	fread(&v1,sizeof(v1),1,dati);
	for(i=0;i<num;i++)
		{
		if(v1[i]!=',') {v[k][j]=v1[i];j++;}
		else {v[k][j]='\0';k++;j=0;}
		}
	v[k][j]='\0';
	for(i=0;i<6;i++)
	{
		if(i==0) natt=atoi(v[i]);
		if(i==1) ncreo=atoi(v[i]);
		if(i==2) nmod=atoi(v[i]);
		if(i==3) ent=atoi(v[i]);
		if(i==4) enp=atoi(v[i]);
	}
	fclose(dati);
	pattern=2*(natt-1)*ncreo*nmod;
	if(pattern>150||enp>300||natt>10||ncreo>10||nmod>10) exit(0);

	dati=fopen("creodi","r");
	for(i=0;i<ncreo;i++)
	{
		j=0;carattere=0;
		while(carattere!=10)
		{
			carattere=fgetc(dati);
			if (carattere!='"')
			{
				creodi[i][j]=carattere;
				++j;
			}
		}
		creodi[i][j-1]='\0';
	}
	fclose(dati);

	dati=fopen("modali","r");
	for(i=0;i<nmod;i++)
	{
		j=0;carattere=0;
		while(carattere!=10)
		{
			carattere=fgetc(dati);
			if (carattere!='"')
			{
				modali[i][j]=carattere;
				++j;
			}
		}
		modali[i][j-1]='\0';
	}
	fclose(dati);

	dati=fopen("attori","r");
	for(i=0;i<natt;i++)
	{
		j=0;carattere=0;
		while(carattere!=10)
		{
			carattere=fgetc(dati);
			if (carattere!='"')
			{
				attori[i][j]=carattere;
				++j;
			}
		}
		attori[i][j-1]='\0';
		strcpy(valore,"   ");
		strcpy(operator[i+1],valore);
		strcat(operator[i+1],attori[i]);
		for(k=0;k<=(17-strlen(operator[i+1]));++k)
			fine[k]=32;fine[k]='\0';

		strcat(operator[i+1],fine);
	}
	fclose(dati);
return(0);
}

risposte(char att[])
{
	FILE *dati;char attori[13];
	int num,numliste,i,j;
	float cecita1,cecita2,rifiuto_effettivo;
	float disis_espressa,disis_ricevuta,complessita;
	float unita[151][16],inverti[151],valore,a1,a2,neg;
	struct file{
		       char dim[4];
		       char creo[30];
		       char mod[30];
		       char att[10];
		       char val[5];
		} agenzie;

	for(i=1;i<=pattern;i++) inverti[i]=0;

	strcpy(attori,att);
	strcat(attori,".DAT");
	dati=fopen(attori,"rb");
	num=filesize(dati)/79;
	numliste=num/15;
	if(num<=0) {fclose(dati);exit(0);}
	for(i=1;i<=2*numliste;i+=2)
	{
		for(j=1;j<=numinput;j++)
		{
			fread(agenzie.dim,4,1,dati);
			fread(agenzie.creo,30,1,dati);
			fread(agenzie.mod,30,1,dati);
			fread(agenzie.att,10,1,dati);
			fread(agenzie.val,5,1,dati);
			agenzie.val[5]='\0';
			unita[i][j]=atof(agenzie.val)/10;
			unita[i+1][j]=atof(agenzie.val)/10;
			if(j==1) cecita1=unita[i][j];
			if(j==2) cecita2=unita[i][j];
			if(j==3) rifiuto_effettivo=unita[i][j];
			if(j==4) disis_espressa=unita[i][j];
			if(j==5) disis_ricevuta=unita[i][j];
			if(j==15) complessita=unita[i][j];
			if(unita[i][j]>1) unita[i][j]=1;
			if(unita[i+1][j]>1) unita[i][j]=1;
		}
		inverti[i]=sigma(cecita1,cecita2,rifiuto_effettivo,
				disis_espressa,disis_ricevuta,complessita);
	}
	fclose(dati);

	for(i=1;i<=2*numliste;i+=2)
	{
		neg=1-(inverti[i]/3);
		a1=1/(1+1-neg);a2=1-a1;
		inverti[i]=inverti[i]/2;
		if(inverti[i]>1) inverti[i]=1;
		for(j=1;j<=numinput;j++)
		{

			ai[i][j]=ai[i+1][j]=unita[i][j];
			if(unita[i][j]>.5) {
			valore=2*unita[i][j]-1;
			valore=inverti[i]*valore;
			target[i][j]=unita[i][j]-valore;
			target[i+1][j]=unita[i][j]; }
			else    {
			valore=1-2*unita[i][j];
			valore=inverti[i]*valore;
			target[i][j]=unita[i][j]+valore;
			target[i+1][j]=unita[i][j]; }

		}
		ai[i][numinput+1]=a1;
		ai[i+1][numinput+1]=a2;
	}
numinput=numinput+1;
return(0);
}

pesi(void)
{
	int i,j;
	randomize();
	for(i=1;i<=numhidden;i++)
	{
		for(j=1;j<=numinput;j++)
			w_i_h[i][j]=frand()*.5;
	}

	for(i=1;i<=numoutput;i++)
	{
		for(j=1;j<=numhidden;j++)
			w_h_o[i][j]=frand()*.5;
	}
return(0);
}


	/* calcola */

calcola(void)
{
	register int i,j;
	float net;
	for (i=1;i<=numhidden;i++)
	{
		net=0;
		for (j=1;j<=numinput;j++)
			net+=ai[pat][j]*w_i_h[i][j];
		if(net>99) net=99;if(net<-99) net=-99;
		ah[i]=1/(1+ pow(NEPER,-(net+bias_h[i])));

	}

	for (i=1;i<=numoutput;i++)
	{
		net=0;
		for (j=1;j<=numhidden;j++)
			net+=ah[j]*w_h_o[i][j];
		if(net>99) net=99;if(net<-99) net=-99;
		ao[i]=1/(1+ pow(NEPER,-(net+bias_o[i])));
		if(bip==1&& ruota==1)
			aoprima[pat][i]=ao[i];
	}
return(0);
}

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

long filesize(FILE *questio)
{
	long curpos,length;
	curpos=ftell(questio);
	fseek(questio,0l,SEEK_END);
	length=ftell(questio);
	fseek(questio,curpos,SEEK_SET);
	return(length);
}

cornice(char titolo[])
{
	int i;int first,back;
	if(strcmp(titolo," FORWARD CON INVERTITORE SFUMATO "))
			{first=1;back=7;} else {first=7;back=1;}
	textmode(C80);textbackground(back);textcolor(first);
	gotoxy(4,3);cprintf("\C9");gotoxy(77,3);cprintf("\BB");
	for(i=5;i<=76;i++) {gotoxy(i,3);cprintf("\CD");}
	for(i=4;i<=23;i++) {gotoxy(4,i);cprintf("\BA");}
	for(i=4;i<=23;i++) {gotoxy(77,i);cprintf("\BA");}
	gotoxy(4,23);cprintf("\C8");gotoxy(77,23);cprintf("\BC");
	gotoxy(5,23);for(i=1;i<=72;i++) cprintf("\CD");
	textbackground(4);textcolor(14);
	gotoxy(40-strlen(titolo)/2,3);cprintf("%s",titolo);
return(0);
}

ctr(long unsigned conta)
{

	if(bip==1 && pat==pattern && ruota==turni)
			{salva_dati(conta);bip=0;printf("\a");}

	if (ruota==turni) {cambia();ruota=0;};

	if (bioskey(1)) key=fermo();

	if(key=='S') {pronto=1;key=0;}
	if (key=='P' && gra==1) {gra=3;key=0;grafmode();tavola(conta);}
	if (key!=0 && gra==3) {
			gra=1;key=0;
			closegraph();textbackground(15);
			clrscr();
			etichette();
			}

	if (key=='I' && gra==1)
					{gra=0;grafmode();etichette_graf();
					key=0;}
	else if (key=='I' && gra==0)
					{closegraph();
					textbackground(15);
					clrscr();
					etichette();
					key=0;gra=1;}
	if (key=='R' && gra==1)
					{gra=5;grafmode();quadro_rete();
					key=0;settextstyle(0,0,0);}
	else if (key=='R' && gra==5)
					{closegraph();
					textbackground(15);
					clrscr();
					etichette();
					key=0;gra=1;}
	if (key=='A' && gra==1)
					{gra=6;grafmode();quadro_ana();
					key=0;settextstyle(0,0,0);}
	else if (key=='A' && gra==6)
					{closegraph();
					textbackground(15);
					clrscr();
					etichette();
					key=0;gra=1;}

	if (key=='E' && gra==1)
					{gra=4;grafmode();
					key=0;}
	if (key=='E' && gra==4)
					{closegraph();
					textbackground(15);
					clrscr();
					etichette();
					key=0;gra=1;}

	else if (key=='T' && gra==1)
					{key=0;gra=2;grafmode();
					quadro_pesi();}
	else if(key=='T' && gra==2)
					{closegraph();
					textbackground(15);
					clrscr();
					etichette();
					key=0;gra=1;}
return(0);
}

fermo()
{
	char car;
	for(;;)
		{
		car=getch();
		if (car=='i') car='I';
		if (car=='t') car='T';
		if (car=='p') car='P';
		if (car=='e') car='E';
		if (car=='s') car='S';
		if (car=='r') car='R';
		if (car=='a') car='A';
		if (car!=' ') return(car);
		}
}

grafmode(void)
{
	driver=VGA;mode=VGAHI;
	initgraph(&driver,&mode,"");
	if (gra==0||gra==4) {quadro();}
return(0);
}

graf_pesi(long unsigned conta)
{
	int i,j;
	int base,altezza;
	int num=0;
	char work[85];
	int static rech[241],reco[226];
	int static bip=0;
	int spessore=1;
	int x=88;
	if (bip==0) {	for(i=1;i<=225;i++) reco[i]=230;
			for(i=1;i<=240;i++) rech[i]=230; }
	bip=1;
	base=230;
	gcvt((long)conta/pattern,10,work);
	setfillstyle(1,0);
	bar(300,10,400,30);
	setcolor(12);
	outtextxy(300,10,work);
	for (i=1;i<=numhidden;i++)
	{
		for (j=1;j<=numinput;j++)
		{
			setfillstyle(1,0);
			++num;
			altezza=(int) base-((bias_h[i]+w_i_h[i][j])*5);
			if(altezza<=1) altezza=2;
			if(altezza>=440) altezza=439;
			bar(x,rech[num],x+spessore,base);
			rech[num]=altezza;
			setfillstyle(1,4);
			bar(x,altezza,x+spessore,base);
			x+=spessore;
		}
	}
	x=330;
	num=0;
	for (i=1;i<=numoutput;i++)
	{
		for (j=1;j<=numhidden;j++)
		{
			setfillstyle(1,0);
			++num;
			altezza=(int) base-((bias_o[i]+w_h_o[i][j])*5);
			if(altezza<=1) altezza=2;
			if(altezza>=440) altezza=439;
			bar(x,reco[num],x+spessore,base);
			reco[num]=altezza;
			setfillstyle(1,2);
			bar(x,altezza,x+spessore,base);
			x+=spessore;
		}
	}

return(0);
}

quadro(void)
{
	register i;
	int y=360;int x;
	char work[85];
	setcolor(3);
	line(30,40,639,40);
	line(30,365,639,365);
	line(639,40,639,365);
	line(30,40,30,365);

	if(gra==4) {
	settextstyle(0,0,2);
	setcolor(3);outtextxy(200,380,"ERRORE GLOBALE");
	settextstyle(0,0,1);
	setcolor(12);
	setfillstyle(1,0);
	for (i=0;i<=10;i++)
	{
		gcvt(i*.1,2,work);
		if(i==0 && i==10) x=8; else x=1;
		outtextxy(x,y,work);
		y-=32;
	}
	}
	settextstyle(0,0,2);
	setcolor(10);
	outtextxy(40,20,att);
	settextstyle(0,0,1);
	setcolor(12);
	setfillstyle(1,0);

return(0);
}


clear()
{
	setcolor(0);
	bar(31,41,638,364);
	setfillstyle(1,0);
	return(0);
}

grafo(long unsigned conti)
{
	int static schermo,x,y[16],pos[16];
	register i,j;float oscilla;
	int static epoca=0;
	char work[85];
	int static vedi=1;
	schermo++;
	if (schermo==607)
		{
			clear();
			schermo=0;x=31;
		}
	if(epoca==0)
	{
		setcolor(0);
		bar(300,20,400,30);
		gcvt((long)conti/pattern,10,work);
		setcolor(4);
		outtextxy(300,20,work);
	}
	epoca++;
	if(epoca==100) epoca=0;

	if (vedi==1)  {x=31;for(i=1;i<=15;i++) y[i]=pos[i]=365-i*20;vedi=0;}

	for (i=1;i<=numoutput;i++)
		if (vedi!=1) {
			setcolor(i);
			oscilla=pos[i]-(target[pat][i]-ao[i])*100;
			if (oscilla<41) oscilla=41;
			if(oscilla>364) oscilla=364;
			line(x,y[i],x+1,oscilla);
			y[i]=oscilla;
			}
	x++;
return(0);
}

cambia()
{
	++pat;
	if(pat>pattern && pronto==1) {bip=1;pronto=0;}
	if (pat>pattern) {pat=1;global_error=0;}

return(0);
}


scrivi(unsigned long num)
{
	int i,x,y;
	float perc;
	textbackground(15);textcolor(1);
	gotoxy(63,7);cprintf("%c%ld%c",' ',num,' ');
	gotoxy(39,7);cprintf("%c%ld%c",' ',(long)num/pattern,' ');

	x=5;y=12;
	for (i=1;i<=numoutput;i++)
	{
		textbackground(2);textcolor(1);
		gotoxy(x,y);cprintf("%s","      ");
		gotoxy(x,y);cprintf("%3.2f%c",errore_dim[i]/pattern,'%');
		x+=11;
		if(i==7) {y=15;x=5;}
		if(i==14) {y=18;x=38;}
	}
		textbackground(15);textcolor(1);
		gotoxy(43,22);cprintf("%c%2.6f%c",' ',global_error,' ');
		perc=(float)record/3968*100;
		textbackground(4);textcolor(15);
		gotoxy(67,22);cprintf("%d ",num_file);
		textbackground(15);textcolor(1);
		gotoxy(69,22);cprintf("%s","       ");
		gotoxy(69,22);cprintf(" %2.2f%c",perc,'%');
	return(0);
}

etichette(void)
{
		int i,x,y;char titolo[50];
		textcolor(15);textbackground(1);clrscr();
		strcpy(titolo," FORWARD CON INVERTITORE SFUMATO ");
		cornice(titolo);
		textcolor(15);textbackground(4);
		gotoxy(6,7);cprintf("%s"," ATTORE :");
		textcolor(1);textbackground(15);
		gotoxy(15,7);cprintf("%c%s%c",' ',att,' ');
		textcolor(15);textbackground(4);
		gotoxy(26,22);cprintf("%s"," ERRORE GLOBALE :");
		textcolor(15);textbackground(4);
		gotoxy(6,22);cprintf("%s"," PATTERNS :");
		textcolor(1);textbackground(15);
		gotoxy(17,22);cprintf("%c%d%c",' ',pattern,' ');
		textcolor(15);textbackground(4);
		gotoxy(56,22);cprintf("%s"," FILE_GRA :");


		textcolor(15);textbackground(4);
		gotoxy(30,7);cprintf("%s"," EPOCHE :");
		textcolor(15);textbackground(4);
		gotoxy(55,7);cprintf("%s"," CICLI :");

		x=5;y=11;
		for (i=1;i<=numoutput;i++)
		{
		textbackground(4);textcolor(14);
		gotoxy(x,y);cprintf("%c%s%c",' ',dim[i-1],' ');
		x+=11;
		if (i==7) {y=14;x=5;}
		if (i==14) {y=17;x=38;}
		}
return (0);
}

quadro_pesi(void)
{
	register i;
	int y=230;int x=35;
	char work[85];
	setcolor(14);
	line(1,1,639,1);
	line(1,440,639,440);
	line(639,1,639,440);
	line(1,1,1,440);
	setcolor(3);
	settextstyle(0,0,2);
	outtextxy(280,445,att);
	settextstyle(0,0,1);
	setcolor(3);
	line(83,10,83,435);
	line(560,10,560,435);
	setcolor(11);
	setfillstyle(1,0);
	for (i=0;i<=5;i++)
	{
		gcvt(i*10,2,work);
		outtextxy(x,y-10,work);
		outtextxy(570,y-10,work);
		y-=50;
	}
	y=280;
	for (i=-1;i>-5;i--)
	{
		gcvt(i*10,2,work);
		outtextxy(x,y-10,work);
		outtextxy(570,y-10,work);
		y+=50;
	}

return(0);
}

tavola(unsigned long num)
{
	int i,j;
	int x,y,color;
	char work1[80],work2[80];
	float diff[16],diff1[16];
	for (i=1;i<=numoutput;++i)
	{
		for (j=1;j<=numhidden;++j)
			diff[i]=w_h_o[i][j]+bias_o[i];

	}
	for (i=1;i<=numinput;++i)
	{
		for (j=1;j<=numhidden;++j)
			diff1[i]=w_i_h[j][i]+bias_h[j];

	}
	settextstyle(0,0,4);
	setcolor(12);
	outtextxy(170,1,"DIMENSIONI");
	gcvt((long)num/pattern,10,work1);
	settextstyle(0,0,0);
	setcolor(15);
	outtextxy(10,10,"EPOCA :");outtextxy(80,10,work1);
	outtextxy(140,60,"INPUT");
	outtextxy(210,60,"OUTPUT");
	outtextxy(460,60,"INPUT");
	outtextxy(530,60,"OUTPUT");

	x=10;y=80;
	for(i=1;i<=numoutput;i++)
	{
		setcolor(11);
		gcvt(diff[i],3,work1);
		gcvt(diff1[i],3,work2);
		settextstyle(0,0,2);
		outtextxy(x,y,dim[i-1]);

		if (diff[i]>0)
			{
				setcolor(2);
				color=2;
			}
			else {
				setcolor(4);
				diff[i]*=-1;
				color=4;
				}
		if(diff[i]>15)
			{	diff[i]=15;
				circle(x+150,y+20,diff[i]*2);
				setfillstyle(1,color);
				floodfill(x+150,y+20,color);
				setcolor(15);
				circle(x+150,y+20,5);
				setfillstyle(1,15);
				floodfill(x+150,y+20,15);
			}
		else
			{	circle(x+150,y+20,diff[i]*2);
				setfillstyle(1,color);
				if (diff[i]!=0) floodfill(x+150,y+20,color);
			}
		setcolor(color);
		settextstyle(0,0,0);
		outtextxy(x+40,y+20,work1);

		if (diff1[i]>0)
			{
				setcolor(2);
				color=2;
			}
			else {
				setcolor(4);
				diff1[i]*=-1;
				color=4;
				}
		if(diff1[i]>15)
			{	diff1[i]=15;
				circle(x+220,y+20,diff1[i]*2);
				setfillstyle(1,color);
				floodfill(x+220,y+20,color);
				setcolor(15);
				circle(x+220,y+20,5);
				setfillstyle(1,15);
				floodfill(x+220,y+20,15);
			 }
		else 	 {	circle(x+220,y+20,diff1[i]*2);
				setfillstyle(1,color);
				if (diff1[i]!=0) floodfill(x+220,y+20,color);
			 }
		setcolor(color);
		settextstyle(0,0,0);
		outtextxy(x+40,y+30,work2);
		y+=50;
		if (y>440) {y=80;x=330;}
	}
return(0);
}

graf_error(unsigned long num)
{
	int static schermo,x;
	float static pasterror=40;
	register i,j;
	float attualerror,delta;
	char work[85],rapporto[20];
	int static vedi=0;
	vedi++;
	schermo++;
	if (schermo==607)
		{
			clear();
			schermo=0;x=31;
		}
	setcolor(0);
	bar(300,20,400,30);
	gcvt((long)num/pattern,10,work);
	setcolor(4);
	outtextxy(300,20,work);
	if (vedi==1)  x=31;

	if (global_error<1)       {delta=318;strcpy(rapporto, "x 1");}
	else if (global_error>1 && global_error<10)
		{delta=31.8;strcpy(rapporto,"x 10");}
	else if (global_error>10 && global_error<100)
		{delta=3.18;strcpy(rapporto,"x 100");}
	else if (global_error>100 && global_error<1000)
		{delta=.318;strcpy(rapporto,"x 1000");}
	else if (global_error>1000){delta=.0318;strcpy(rapporto,"x 10000");}

	attualerror=360-global_error*delta;
	if (attualerror<=40) attualerror=41;
	line(x,pasterror,x+1,attualerror);
	pasterror=attualerror;
	x++;
	setcolor(0);
	bar(50,450,100,470);
	setcolor(11);
	outtextxy(50,450,rapporto);
return(0);
}

ctr_file(void)
{
	FILE *dati;char nome[13];
	int mem;int car;
	int long num;
	unsigned long epoca;
	strcpy(nome,att);
	strcat(nome,".wei");
	dati=fopen(nome,"rb");
	num=filesize(dati);
	if(num>0) {
			fread(&epoca,sizeof(long unsigned),1,dati);
			strcpy(operator[1]," SI ");strcpy(operator[2]," NO ");
			ascissa=62;ordinata=19;totale=2;
			limite=ordinata+1;max=1;
			xdestra = 51; xsinistra = 74;
			yalto = ordinata-5; ybasso =limite+1;
			sfondo=1;bordi=14;barre=4;
			finestra(xdestra,xsinistra,yalto,ybasso,sfondo,bordi);
			gotoxy(54,15);
			cprintf("%s %s","L'ATTORE ",att);
			gotoxy(54,16);
			cprintf("%s","E' GIUNTO ALL'EPOCA ");
			textcolor(14);textbackground(4);
			gotoxy(54,17);
			cprintf("%ld",(long)epoca/pattern);
			textcolor(14);textbackground(1);
			gotoxy(54,18);
			cprintf("VUOI CONTINUARE ?");
			car=box(max,ascissa,ordinata,limite,totale,sfondo,bordi,barre);
			if(car==1) { fclose(dati);mem=1;return(mem);}
			if(car==2) {fclose(dati);mem=0;return(mem);}
			if(car==0) {fclose(dati);mem=-1;return(mem);}
			}
			mem=0;
	fclose(dati);

return(mem);
}

salva_dati(unsigned long epoca)
{
	FILE *dati;
	int i,j;
	char nome[13];
	strcpy(nome,att);
	strcat(nome,".wei");
	dati=fopen(nome,"wb");
	fwrite(&epoca,sizeof(unsigned long),1,dati);
	for(i=1;i<=numhidden;i++)
	{
		for (j=1;j<=numinput;j++)
			fwrite(&w_i_h[i][j],sizeof(float),1,dati);
	}

	for(i=1;i<=numoutput;i++)
	{
		for(j=1;j<=numhidden;j++)
			fwrite(&w_h_o[i][j],sizeof(float),1,dati);
	}

	for(i=1;i<=numhidden;i++)
		fwrite(&bias_h[i],sizeof(float),1,dati);

	for(i=1;i<=numoutput;i++)
		fwrite(&bias_o[i],sizeof(float),1,dati);

	for(i=1;i<=numoutput;i++)
		fwrite(&delta_out[i],sizeof(float),1,dati);

	fclose(dati);
	salva_testo(epoca);
return(0);
}

unsigned long prendi_dati(void)
{
	FILE *dati;
	int i,j;
	unsigned long epoca;
	char nome[13];
	strcpy(nome,att);
	strcat(nome,".wei");
	dati=fopen(nome,"rb");
	fread(&epoca,sizeof(unsigned long),1,dati);
	for(i=1;i<=numhidden;i++)
	{
		for (j=1;j<=numinput;j++)
			fread(&w_i_h[i][j],sizeof(float),1,dati);
	}

	for(i=1;i<=numoutput;i++)
	{
		for(j=1;j<=numhidden;j++)
			fread(&w_h_o[i][j],sizeof(float),1,dati);
	}

	for(i=1;i<=numhidden;i++)
		fread(&bias_h[i],sizeof(float),1,dati);

	for(i=1;i<=numoutput;i++)
		fread(&bias_o[i],sizeof(float),1,dati);

	for(i=1;i<=numoutput;i++)
		fread(&delta_out[i],sizeof(float),1,dati);

	fclose(dati);
return(epoca);
}

etichette_graf(void)
{
	int i,x=40;
	int color=0;
	for(i=0;i<numoutput;i++)
	{
		settextstyle(0,0,1);
		setcolor(++color);
		outtextxy(x,400,dim[i]);
		x+=40;
	}
	settextstyle(0,0,0);
return(0);
}

salva_testo(unsigned long epoca)
{
	FILE *dati;
	int i,j;
	char nome[13];
	int patt=0,pcreodi=0,pmod=-1;
	float perc;
	strcpy(nome,att);
	strcat(nome,".err");
	dati=fopen(nome,"w");
	fprintf(dati,"%s %2.8f %s %s %s %ld\n","ERRORE GLOBALE  :",
	global_error,"      ",att,"        EPOCA :",(long)epoca/pattern);
	fprintf(dati,"\n");fprintf(dati,"\n");fprintf(dati,"\n");

	for(i=1;i<=pattern;i+=2)
	{
	pmod++;
	if (pmod==nmod) {pmod=0;pcreodi++;}
	if (pcreodi==ncreo) {pcreodi=0;patt++;}
	if (patt==saltalo) patt++;
	if (patt>=natt) patt=0;

	fprintf(dati,"%s %s %s\n",attori[patt],creodi[pcreodi],modali[pmod]);
	fprintf(dati,"%s%1.4f        ","Errore di Lista 1 :",errorelista[i]);
	fprintf(dati,"%s%1.4f ","Errore di Lista 2:",errorelista[i+1]);
	fprintf(dati,"\n");fprintf(dati,"\n");

		for(j=0;j<numoutput;j++)
			fprintf(dati,"%s ",dim[j]);
		fprintf(dati,"\n");

		for(j=1;j<=numoutput;j++)
		{
			perc=100*fabs(target[i][j]-aoprima[i][j]);
			fprintf(dati,"%c%2.0f%c ",' ',perc,'%');
		}
		fprintf(dati,"\n");
		for (j=1;j<=numoutput;j++)
		{
			perc=100*fabs(target[i+1][j]-aoprima[i+1][j]);
			fprintf(dati,"%c%2.0f%c ",' ',perc,'%');
		}
	fprintf(dati,"\n");fprintf(dati,"\n");fprintf(dati,"\n");
	}
	fclose(dati);
return(0);
}

quadro_rete()
{
int dm[9][14];
char dim[15][5]={"TrRi","RiTr"," Plu","TTra","TTrb"," Tr ","MeTr",
		 "MoTr","RiRi","MoFo","MMof","MoRi","MeRi"," Ri ","Comp"};
int y = 380, x =-10;
int i,j,driver,mode;
int x1,x2,x3,x5,y1,y2,y3,y4,y5;
int cerchi1,cerchi2,cerchi3;

	x1=x3=x5=-10;
	y1=y2=y3=y4=y5=0;
	x2=-10;

	settextstyle(0,0,2);setcolor(14);
	outtextxy(220,1,"MODELLO MQ");
	outtextxy(110,50,"RETE AD INVERTITORE SFUMATO");

	y1=y-240;x1=x+42;
	for(cerchi1=1;cerchi1<=numoutput;cerchi1++)
	{
		setcolor(11);circle(x1,y1,20);
		setfillstyle(1,11);floodfill(x1,y1,11);
		y2=y-110;x2=x+42;
		for(cerchi2=1;cerchi2<=numhidden;cerchi2++)
		{
			setcolor(4);line(x1,y1+30,x2,y2-20);
			setcolor(1);circle(x2,y2,20);
			setfillstyle(1,1);floodfill(x2,y2,1);
			y3=y+20;x3=x+42;
		if(cerchi1==1)
			{
			for(cerchi3=1;cerchi3<=numoutput;cerchi3++)
				{
				setcolor(4);line(x2,y2+20,x3,y3-30);
				setcolor(10);circle(x3,y3,20);
				setfillstyle(1,10);floodfill(x3,y3,10);
				y5=y-60;x5=x+42;
				x3+=42;
				}
			y4=y-140;
			}
			x2+=42;
		}
		x1+=42;
	}
	x5=18;y5=y-250;y4=y+10;
	for(i=0;i<numoutput;i++)
	{
		settextstyle(0,0,0);
		setcolor(1);
		outtextxy(x5,y5,dim[i]);
		outtextxy(x5,y4,dim[i]);
		x5+=42;
	}

	settextstyle(0,0,2);setcolor(14);
	outtextxy(200,450,"EPOCA :");
	settextstyle(0,0,0);
return(0);
}

rete_grafica(unsigned long num)
{
	int i,x,y;int static appare=0;
	char valore[80];float a;
	x=16;y=140;

	if(appare==0) {settextstyle(0,0,2);setcolor(14);
			setfillstyle(1,0);
			bar(320,450,430,480);
			gcvt((long)num/pattern,10,valore);
			outtextxy(320,450,valore);
			settextstyle(0,0,0);
			}
	appare++;if(appare==10) appare=0;
		setcolor(4);
		setfillstyle(1,11);
		for(i=1;i<=numoutput;i++)
		{
			bar(x,y,x+50,y+8);
			gcvt(ai[pat][i],2,valore);
			outtextxy(x,y,valore);
			x+=42;
		}

	x=16;y=270;
	setcolor(4);
		setfillstyle(1,1);
		for(i=1;i<=numhidden;i++)
		{
			bar(x,y,x+38,y+8);
			a=ah[i];
			if(a<0.01) a=0.011;
			gcvt(a,2,valore);
			outtextxy(x,y,valore);
			x+=42;
		}

	x=16;y=400;
	setcolor(4);
		setfillstyle(1,10);
		for(i=1;i<=numoutput;i++)
		{
			bar(x,y,x+50,y+8);
			gcvt(ao[i],2,valore);
			outtextxy(x,y,valore);
			x+=42;
		}

return(0);
}

scrivi_error(FILE *grafic)
{
	char pausa;int static colonna=0;
	colonna++;
	if(colonna<64) pausa=9; else {pausa=10;colonna=0;}
	fprintf(grafic,"%1.2f%c",global_error,pausa);
return(0);
}

quadro_ana()
{

	int i,x=25,y1=110,y2=425;
	settextstyle(0,0,2);setcolor(14);
	outtextxy(220,1,"MODELLO MQ");
	outtextxy(110,50,"RETE AD INVERTITORE SFUMATO");

	settextstyle(0,0,2);setcolor(14);
	outtextxy(170,450,"EPOCA :");
	settextstyle(0,0,0);
	setcolor(4);
	for(i=0;i<numoutput;i++)
	{	outtextxy(x,y1,dim[i]);
		outtextxy(x,y2,dim[i]);
		x+=40;
	}
return(0);
}

rete_ana(unsigned long num)
{
	int i,j,x,y,x1,color;int static appare=0;
	char valore[80];
	static int mem1[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	static int mem2[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	static int mem3[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	x=40;y=140;

	if(appare==0) {settextstyle(0,0,2);setcolor(14);
			setfillstyle(1,0);
			bar(320,450,430,480);
			gcvt((long)num/pattern,10,valore);
			outtextxy(320,450,valore);
			settextstyle(0,0,0);
			}
	appare++;if(appare==10) appare=0;
		for(i=1;i<=numoutput;i++)
		{
			setcolor(0);circle(x,y,mem1[i]);
			setfillstyle(1,0);floodfill(x,y,0);
			setcolor(11);circle(x,y,(int)(ai[pat][i]*20));
			setfillstyle(1,11);floodfill(x,y,11);
			setcolor(14);line(x,y,x,y+15);
			mem1[i]=(int)(ai[pat][i]*20);
			x1=60;
			for(j=1;j<=numhidden;j++)
			{
				if(w_i_h[j][i]>1) color=10;
				if(w_i_h[j][i]<-1) color=12;
				if(w_i_h[j][i]<1 && w_i_h[j][i]>-1) color=15;
				setcolor(color);
				line(x,y+15,x1,250);
				x1+=37;
			}
			x+=40;
		}

	x=60;y=270;
		for(i=1;i<=numhidden;i++)
		{
			setcolor(0);circle(x,y,mem2[i]);
			setfillstyle(1,0);floodfill(x,y,0);
			if(bias_h[i]>1) color=10;
			if(bias_h[i]<-1) color=12;
			if(bias_h[i]<1 && bias_h[i]>-1) color=15;
			setcolor(color);circle(x,y,(int)(ah[i]*20));
			setfillstyle(1,color);floodfill(x,y,color);
			setcolor(14);line(x,y,x,y+20);line(x,y,x,y-20);
			circle(x,y,1);
			mem2[i]=(int)(ah[i]*20);
			x1=40;
			for(j=1;j<=numoutput;j++)
			{
				if(w_h_o[j][i]>1) color=10;
				if(w_h_o[j][i]<-1) color=12;
				if(w_h_o[j][i]<1 && w_h_o[j][i]>-1) color=15;
				setcolor(color);
				line(x,y+20,x1,385);
			x1+=40;
			}
			x+=37;
		}

	x=40;y=400;
		for(i=1;i<=numoutput;i++)
		{
			setcolor(0);circle(x,y,mem3[i]);
			setfillstyle(1,0);floodfill(x,y,0);
			if(bias_o[i]>1) color=10;
			if(bias_o[i]<-1) color=12;
			if(bias_o[i]<1 && bias_o[i]>-1) color=15;
			setcolor(color);circle(x,y,(int)(ao[i]*20));
			setfillstyle(1,color);floodfill(x,y,color);
			setcolor(14);line(x,y,x,y-15);
			mem3[i]=(int)(ao[i]*20);
			x+=40;
		}

return(0);
}

int box(int max,int ascissa,int ordinata,int limite,
int totale,int sfondo,int bordi,int barre)
{
	int i=0,min=1,j=1;
	int x=ascissa;int y=ordinata;
	key=0;
	while(key!=13 && key!=27)
	{

		if((j==max && j<=totale && key==0+'P' && max<totale)
		||(j==max && j<=totale && key==0+'Q' && max<totale))
			{ min++;max++;}

		if((j==min && j<=totale && key==0+'I' && min>1)
		||(j==min && j<=totale && key==0+'H' && min>1))
			{ min--;max--;}

		if(key==0+'P' || key==0+'Q') {
				y=ordinata;i=min-1;
				if(j==totale) printf("\a");
				if(j<totale) j++;
			     }
		if(key==0+'I' || key==0+'H') {
				y=ordinata;i=min-1;
				if(j==1) printf("\a");
				if(j>1) j--;
			     }


		while (y < limite)
		{
			i ++;y++;
			if(i==j) {textcolor(bordi);textbackground(barre);}
			else 	 {textcolor(bordi);textbackground(sfondo);}
			gotoxy(x,y);cprintf("%s",operator[i]);
		}
		key=getch();
	}
	if(key==27) j=0;
	return(j);
}

int finestra (int xdestra, int xsinistra, int yalto,
int ybasso, int sfondo, int bordi)
{
	int i,j;
	textcolor(bordi);textbackground(sfondo);
	gotoxy(xdestra,yalto);cprintf(" \C9");
	gotoxy(xsinistra,yalto);cprintf("\BB ");
	for(i=xdestra+2;i<=xsinistra-1;i++) {gotoxy(i,yalto);cprintf("\CD");}
	for(i=yalto+1;i<=ybasso-1;i++) {gotoxy(xdestra,i);cprintf(" \BA");}
	for(i=yalto+1;i<=ybasso-1;i++) {gotoxy(xsinistra,i);cprintf("\BA ");}
	for(i=yalto+1;i<ybasso;i++)
	{	for(j=xdestra+2;j<xsinistra;j++) {
				gotoxy(j,i);cprintf(" ");}
	}
	gotoxy( xdestra,ybasso);cprintf (" \C8");
	gotoxy(xsinistra,ybasso);cprintf("\BC ");
	gotoxy(xdestra+2,ybasso);
	for(i=1;i<=(xsinistra - xdestra - 2);i++) cprintf ("\CD");
return(0);
}

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

apri_file(int num_file,unsigned long num)
{
		char numero[16],bnome[13];
		long start;int i;
		bnome[0]='$';
		for(i=1;i<6;i++) bnome[i]=att[i-1];
		bnome[6]='\0';
		gcvt(num_file,2,numero);
		strcat(bnome,numero);
		strcat(bnome,".dat");
		grafic=fopen(bnome,"w");
		start=(long)num/pattern;
		fprintf(grafic,"%s%c",att,10);
		fprintf(grafic,"%s%c%c","ERROR_FF_IS",9,9);
		fprintf(grafic,"%s%ld%c%ld%c","Epoche_",start,'-',start+3968,10);
return(0);
}

azzera(void)
{
	int i;
	for(i=1;i<=numoutput;i++)
		errore_dim[i]=0;
return(0);
}