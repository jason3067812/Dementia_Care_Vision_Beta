#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libraries/camlog/camlog.h"
#define VERSION 210426
#define LINELENGTH 4056
#define DATA_IRCAMERA 12
char bb[LINELENGTH],image[LINELENGTH];
#define TEST 1

int createTextImage(char *time,unsigned char motion,char *image){
	FILE *fout;
	char hexstring[2];
	int j,jbyte;	
	sprintf(bb,"out/t%c%c%c%c%c%c.csv",time[0],time[1],time[3],time[4],time[6],time[7]); 
	fprintf(stderr,"\n\tcreateTextImage(%s):",bb); 
	if((fout=fopen(bb,"w"))==NULL)goto errOpen;	
	if(strlen(image)!=(2*PIXELS+1))goto errPixel;
	for(j=0;j<PIXELS;j++){
		sprintf(hexstring,"%c%c",image[2*j],image[2*j+1]);
		jbyte=strtol(hexstring,NULL,16);
		fprintf(fout,"%03d,",jbyte);
		if(((j+1) % (PIXCOL))==0)fprintf(fout,"\n");
	}
	fclose(fout);
	return(0);
errOpen: fprintf(stderr,"ERROR open to write fails"); return(1);
errPixel: fprintf(stderr,"ERROR %d != 2 * %d + 1",strlen(image),PIXELS); return(1);
}
int txtimage(char *fname){
	FILE *fin=fopen(fname,"r");
	char *time=NULL;
	int jmode=0, iline=0;
	unsigned char motion;
	fprintf(stderr,"\nimage(version=%d) (%s): USAGE: image filename ",VERSION,fname);
	if(fin==NULL)goto err_open;
	while(fgets(bb,LINELENGTH,fin)!=NULL){
		iline++;
		time=strtok(bb,",");
		jmode=atol(strtok(NULL,","));
		if(jmode==DATA_IRCAMERA){
			motion=atol(strtok(NULL,","));
			strcpy(image,strtok(NULL,","));
			createTextImage(time,motion,image);
		}else fprintf(stderr,"\n\tline %d not camera data",iline);
	}
	return(0);
err_open: fprintf(stderr,"\n ERR file open fails"); return(1);
}	
int main(int argc, char **argv){
	if(argc!=2)goto usage;
	txtimage(argv[1]);
	return(0);
usage: fprintf(stderr,"USAGE image filename"); return(1);
}