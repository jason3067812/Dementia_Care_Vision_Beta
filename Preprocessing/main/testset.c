#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libraries/camlog/camlog.h"
void testSet(void){
	FILE *fhex=fopen("testhex.csv","w");
	FILE *fdec=fopen("testdec.csv","w");
	int data[PIXELS], k;
	fprintf(stderr,"\ntestSet(): output stored in testhex.csv and testdec.csv\n");
	for(k=0;k<PIXELS;k++)data[k]=0;
	for(k=0;k<PIXCOL/2;k++)data[k]=255;
	for(k=0;k<PIXROW/2;k++)data[k*PIXCOL]=255;
	for(k=0;k<PIXELS;k++)fprintf(fhex,"%02x",data[k]);
	fclose(fhex);
	for(k=0;k<PIXELS;k++){
		fprintf(fdec,"%03d,",data[k]);
		if(((k+1) % PIXCOL)==0)fprintf(fdec,"\n");
	}
	fclose(fdec);
}	

int main(void){testSet();return(0);}