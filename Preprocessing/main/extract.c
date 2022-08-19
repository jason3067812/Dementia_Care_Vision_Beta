#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct jtime{
	int h;
	int m;
	int s;
} w,limit[2];
#define VERSION 210716
#define MB 5000
int main(int argc, char **argv){
	char bb[MB], bb2[MB]; int k;
	if(argc!=3)goto errArg;
	for(k=0;k<2;k++){
		strcpy(bb2,argv[k+1]);
		limit[k].h=atol(strtok(bb2,":"));
		limit[k].m=atol(strtok(NULL,":"));	
	}
	fprintf(stderr,"extracting from %02d:%02d to %02d:%02d", limit[0].h, limit[0].m,
		limit[1].h,limit[1].m);
	while(fgets(bb,MB,stdin)){
		k++;
		strcpy(bb2,bb);
		w.h=atol(strtok(bb2,":"));
		w.m=atol(strtok(NULL,":"));
		w.s=atol(strtok(NULL,","));	
		if(w.h>=limit[0].h && w.m>limit[0].m)break;
	}
	fprintf(stderr,"\n From: '%s' line %d",argv[1],k); 
	while(fgets(bb,MB,stdin)){
		k++;
		strcpy(bb2,bb);
		w.h=atol(strtok(bb2,":"));
		w.m=atol(strtok(NULL,":"));
		w.s=atol(strtok(NULL,","));	
		if(w.h>=limit[1].h && w.m>limit[1].m)break;
		fprintf(stdout,"%s",bb);
	}
	fprintf(stderr,"\n   To: '%s' line %d",argv[2],k);
	return(0);
errArg: fprintf(stderr,"USAGE: extract hh:mm hh:mm < inputFile > outputFile"); return(2);	
}