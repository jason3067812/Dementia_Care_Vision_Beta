#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../libraries/camlog/camlog.h"
#define VERSION 210611
#define HIST_SPECIAL 0  /* shisto[HIST_SPECIAL]=2 for file integrity */
#define HIST_SWITCH 1
#define HIST_CAMERA 2
#define HIST_JMODE 3
#define DATA_POWER_FAILURE 99
#define DATA_CAMERA_LENGTH 1551
#define DATA_SWITCH_LENGTH 13

#define LINELENGTH 4056
#define DATA_IRCAMERA 12
#define HOTPIX 4
char bb[LINELENGTH];  

struct CelciusStat celciusStatAll={0,0,-10.0,100.0};

struct IRData{
	int h;
	int m;
	int s;
	double hr;
	int jmode;
	int pir;
	char image[LINELENGTH];
};

struct CelciusStat checkCameraDataStat(char *image){
	int j;
	char hexstring[3]={"\0"};
	int jbyte;
	double jCelcius;
	struct CelciusStat celciusStat={0,0,-10.0,100.0};
	for(j=0;j<PIXELS;j++){
		sprintf(hexstring,"%c%c",image[2*j],image[2*j+1]);
		jbyte=strtol(hexstring,NULL,16);
		if(jbyte>252)celciusStat.nhigh++;
		if(jbyte<2)celciusStat.nlow++;
		jCelcius= (TMIN+jbyte)/10.0;
/*		fprintf(fout,"\n\t\t %s,%02d,%4.1lf",hexstring,jbyte,jCelcius); */
		if(jCelcius>celciusStat.max)celciusStat.max=jCelcius;
		if(jCelcius<celciusStat.min)celciusStat.min=jCelcius;
		celciusStat.mean+=jCelcius;
	}
	celciusStat.mean/= (double) PIXELS;
	for(j=0;j<PIXELS;j++){
		sprintf(hexstring,"%c%c",image[2*j],image[2*j+1]);
		jbyte=strtol(hexstring,NULL,16);
		jCelcius = (TMIN+jbyte)/10.0;
		celciusStat.sd+=(jCelcius-celciusStat.mean)*(jCelcius-celciusStat.mean);
   }
   celciusStat.sd/=(double) PIXELS;
   celciusStat.sd = sqrt(celciusStat.sd);
   return(celciusStat);
}


int main(int argc, char **argv){
	int j, jline=0, jlength=0,histo[4]={0,0,0,0}, histomotion=0;
	struct IRData irdata,irstart;
	struct CelciusStat celciusStat;
	FILE *fin,*fout[2];
	if(argc==1)sprintf(bb,"esp.csv");
	else strcpy(bb,argv[1]);
	fprintf(stderr,"chek(%s): To check datalogESP files for integrity\n\tUSAGE(): chek filename"
	"\n\t elif no filename default to 'esp.csv' \n\t --> 'out/cheksimp.csv', out/chekfull.csv\n", bb);
	if((fin=fopen(bb,"r"))==NULL)goto errFileIn;
	fout[0]=fopen("out/cheksimp.csv","a");
	fout[1]=fopen("out/chekfull.csv","a");

	for(j=0;j<2;j++)fprintf(fout[j],"TMIN=%d TMAX=%d \n line,00:00:00,  hours,nhi,nlo, max, min, mean, sd, pir ", TMIN,TMAX);

	while(fgets(bb,LINELENGTH,fin)){
		jline++;
		jlength=strlen(bb);
		if(jlength>1 && jlength<=DATA_SWITCH_LENGTH)histo[HIST_SWITCH]++;
		else if(jlength==DATA_CAMERA_LENGTH|| jlength==(DATA_CAMERA_LENGTH-1)){
			histo[HIST_CAMERA]++;
			if(bb[12]=='1')histomotion++;
			irdata.h=atol(strtok(bb,":"));
			irdata.m=atol(strtok(NULL,":"));
			irdata.s=atol(strtok(NULL,","));
			irdata.hr= (double)((irdata.h*60 + irdata.m)*60 +irdata.s)/3600.0;
			irdata.jmode=atol(strtok(NULL,",")); irdata.pir=atol(strtok(NULL,",")); 
			strcpy(irdata.image,strtok(NULL,","));
			if(jline==1)irstart=irdata;
			celciusStat=checkCameraDataStat(irdata.image);
			celciusStatAll.nhigh+=celciusStat.nhigh;
			celciusStatAll.nlow+=celciusStat.nlow;
			celciusStatAll.mean+=celciusStat.mean;	
			sprintf(bb,"\n%5d,%02d:%02d:%02d,%7.4f,%3d,%3d,%4.1lf,%4.1lf,%5.2lf,%5.2lf,%d",
				jline,irdata.h,irdata.h,irdata.s,irdata.hr,celciusStat.nhigh,celciusStat.nlow,
				celciusStat.max,celciusStat.min,celciusStat.mean,celciusStat.sd,irdata.pir);
			if(celciusStat.nhigh>0 || celciusStat.nlow<0)fprintf(fout[0],"%s",bb);
			fprintf(fout[1],"%s",bb);	
		}else{
			bb[strlen(bb)-1]='\0';
			irdata.h=atol(strtok(bb,":"));
			irdata.m=atol(strtok(NULL,":"));
			irdata.s=atol(strtok(NULL,","));
			irdata.hr= (double)((irdata.h*60 + irdata.m)*60 +irdata.s)/3600.0;
			irdata.jmode=atol(strtok(NULL,","));
			for(j=0;j<2;j++)fprintf(fout[j],
				"\n%5d,%02d:%02d:%02d,%.4f,%3d,%s",jline,irdata.h,irdata.h,irdata.s,irdata.hr,irdata.jmode,strtok(NULL,","));
			if(irdata.jmode==DATA_POWER_FAILURE)histo[HIST_JMODE]++;
			else histo[HIST_SPECIAL]++;
		}
	}
	fclose(fin);
	celciusStatAll.mean/=jline;
	fprintf(fout[0],"\nlns=%d,mode(s,c,99,other)=%d,%d,%d,%d,",jline,histo[HIST_SWITCH],histo[HIST_CAMERA],
		histo[HIST_JMODE], histo[HIST_SPECIAL]);
	fprintf(fout[0],"\n\t from %.4f -> %.4f,PIR=%d Pix hi,%d,Pix lo,%d, meanT=%.1f\n",
			irstart.hr,irdata.hr,histomotion,celciusStatAll.nhigh,celciusStatAll.nlow,celciusStatAll.mean);
	for(j=0;j<2;j++)fclose(fout[j]);
	return(0);
errFileIn: fprintf(stderr,"ERR no input file"); return(1);
}
	
	
	