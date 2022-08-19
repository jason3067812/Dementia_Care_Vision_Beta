#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libraries/camlog/camlog.h"
#define VERSION 210607
#define LINELENGTH 4056
#define DATA_IRCAMERA 12
#define HOTPIX 4
char bb[LINELENGTH];
FILE *fin, *fdiag, *fpixthre, *fmean;
int nhot;
char jtime[24]={"/0"};
struct State{
	char time[16];
	int motion;
	int heat;
	float hr;
};
struct State state[2];

int detectHotpix(char *image, int wst){
	char hexstring[2];
	int j,jbyte,nhot=0;
	if((strlen(image)!=(2*PIXELS+1)) && (strlen(image)!=(2*PIXELS)))goto errPixel;
	for(j=0;j<PIXELS;j++){
		sprintf(hexstring,"%c%c",image[2*j],image[2*j+1]);
		jbyte=strtol(hexstring,NULL,16);
		if(jbyte>(wst-TMIN))nhot++;
/*		if(((j+1) % (PIXCOL))==0)fprintf(fpixthre,"\n"); */
	}
	if(nhot>0)fprintf(fdiag,"\n%s,%d",jtime,nhot);
	return(nhot);
errPixel: fprintf(stderr,"\nERROR %d != 2 * %d",strlen(image),PIXELS); return(-2);	
}
int analyse(char *fname,int hotpix, int wst){
	int jmode=0, iline=0;
	state[0].motion=-1; state[0].heat=-1;
	if((fin=fopen(fname,"r"))==NULL)goto err_open;
	if((fpixthre=fopen("out/pixthre.csv","a"))==NULL)goto err_open;
	if((fdiag=fopen("out/diag.csv","a"))==NULL)goto err_open;
	fprintf(stderr,"\ndetectHotpix(%d) %s hotpix=%d wst=%d:",VERSION,fname,hotpix,wst);
	fprintf(fpixthre,"\ndetectHotpix(%d) %s hotpix=%d wst=%d:",VERSION,fname,hotpix,wst);
	fprintf(fdiag,"\n************* detectHotpix(%d) %s hotpix=%d wst=%d ****************",
		VERSION,fname,hotpix,wst);
	while(fgets(bb,LINELENGTH,fin)!=NULL){
		if(strlen(bb)<PIXELS)continue;
		iline++;
		strcpy(jtime,strtok(bb,","));
		jmode=atol(strtok(NULL,","));
		if(jmode!=DATA_IRCAMERA)continue;
		strcpy(state[1].time,jtime);
 		state[1].hr=(jtime[0]-'0')*10 + (jtime[1]-'0') 
 			+ (float) ((jtime[3]-'0')*10+(jtime[4]-'0'))/60.0 
 			+ (float) ((jtime[6]-'0')*10+(jtime[7]-'0'))/3600.0;

		state[1].motion=atol(strtok(NULL,","));
		nhot=detectHotpix(strtok(NULL,","),wst);
		if(nhot<hotpix)state[1].heat=0; else state[1].heat=1;  	
		if(state[1].motion!=state[0].motion || state[1].heat!=state[0].heat){
			if(iline!=1)fprintf(fpixthre,"\n%c%c:%c%c:%c%c,%6.3f,%d,%d",
				state[1].time[0],state[1].time[1],state[1].time[3],
				state[1].time[4],state[1].time[6],state[1].time[7]-1,  
				state[1].hr-0.001,state[0].motion,state[0].heat);	
			fprintf(fpixthre,"\n%c%c:%c%c:%c%c,%6.3f,%d,%d",
				state[1].time[0],state[1].time[1],state[1].time[3],
				state[1].time[4],state[1].time[6],state[1].time[7],  
				state[1].hr,state[1].motion,state[1].heat);	
			state[0]=state[1];
		}
	}
	fclose(fin);
	fclose(fpixthre);
	fclose(fdiag);
	return(0);
err_open: fprintf(stderr,"ERR file open fails"); return(1);
}	

int main(int argc, char **argv){
	char fname[64]="test.csv";
	if(argc>1)strcpy(fname,argv[1]);
	if(argc>3)analyse(fname,atol(argv[2]),atol(argv[3]));
	else analyse(fname,HOTPIX,WST);
	return(0);
}