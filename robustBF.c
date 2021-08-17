#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "prime.h"
#include "murmur.h"
#include "2dfilter.h"
#include "initBF.h"
#include "keyBF.h"

static unsigned long int TP=0,TN=0;

unsigned long int **kBF;

void insertSmartBF(char *key)
{
	int i;
	for(i=0;key[i]!='\0';i++);
	insert_keyBF(kBF,key,i);
}

void lookupSmartBF(char *key)
{
	int i;
	for(i=0;key[i]!='\0';i++);
	if(lookup_keyBF(kBF,key,i))
	{
		TP++;
		return;
	}

	TN++;
	return;
	
}


void freeSmartBF()
{
	free_keyBF(kBF);
}

int main()
{
	
	char ch,buff[10240];
	unsigned long int m,n=10000000;
	unsigned long int l,u;
	double err=0.001;
	unsigned long int i,r;
	unsigned long int count=0;
	double fp=0.0;
	FILE *f=fopen("10M_r.txt","w");
	clock_t start, end;
	printf("File initiated!\n");	
	initSeed();
	printf("Seeds initiated!\n");
	m=memory(n,err);
	printf("Memory initiated!\n");
	setDim(m);
	printf("Dimensions initiated!\n");
	kBF=allocate();
	printf("Filters are created!\n");

	printf("Insertion process of %lu\n",n);
	fprintf(f,"Insertion process of %lu\n",n);
	start=clock();
	for(i=0;i<n;i++)
	{
		sprintf(buff,"%lu",i);
		insertSmartBF(buff);
	}
	end=clock();
	double diff=(double)(end-start)/CLOCKS_PER_SEC;
	printf("Total insertion:%lu\n",i);
	fprintf(f,"Total insertion:%lu\n",i);
	printf("Elapsed Time of insertion:%f\n\n", (double)(end-start)/CLOCKS_PER_SEC);
	fprintf(f,"Elapsed Time of insertion:%f\n\n", (double)(end-start)/CLOCKS_PER_SEC);

	n=i;
	///////////////////
	// Lookup process
	///////////////////
	printf("Lookup process of %lu\n",n);	
	fprintf(f,"Lookup process %lu\n",n);


	///////////////////////
	//Same set
	///////////////////////
	start=clock();
	i=0;fp=0.0;
	for(i=0;i<n;i++)
	{
		sprintf(buff,"%lu",i);
		lookupSmartBF(buff);
	}
	end=clock();
	fp=(TN)/(double)n;
	//fp=(double)(TP+TN+CTN)/(double)(TP+TN+CTN+FN+FP);
	diff=(double)(end-start)/CLOCKS_PER_SEC;
	
	printf("\nSame set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100,(fp));
	printf("Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	fprintf(f,"\nSame set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100,(fp));
	//fprintf(f,"Millions insertion:%lf\n",(double)n/diff);
	fprintf(f,"Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);

	printf("Summary:\n");
	printf("TP: %lu\tTN:  %lu\n",TP,TN);
	fprintf(f,"Summary:\n");
	fprintf(f,"TP: %lu\tTN:  %lu\n",TP,TN);
	
	TP=0;TN=0;

	
	
	///////////////////////
	//Mixed set
	///////////////////////
	start=clock();
	i=0;l=n/2;u=2*l+l;fp=0.0;
	for(i=l;i<u;i++)
	{
		sprintf(buff,"%lu",i);
		lookupSmartBF(buff);
	}
	end=clock();
	//fp=(double)(found-l)/(double)n;
	fp=(double)(TP-l)/(double)(n);
	diff=(double)(end-start)/CLOCKS_PER_SEC;
	printf("\nMixed set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100.0,fp);
	//printf("Found: %lu\tupper:%lu\tlower:%lu\n",found,u,l);
	printf("Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	fprintf(f,"\nMixed set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100.0,fp);
	//fprintf(f,"Millions insertion:%lf\n",(double)n/diff);
    fprintf(f,"Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);

	printf("Summary:\n");
	printf("TP: %lu\tTN:  %lu\n",TP,TN);
	fprintf(f,"Summary:\n");
	fprintf(f,"TP: %lu\tTN:  %lu\n",TP,TN);
	
	TP=0;TN=0;


	///////////////////////
	//Dijsoint set
	///////////////////////
	start=clock();
	i=0;l=n+1;u=1000*n;fp=0.0;
	for(i=1;i<=n;i++)
	{
		r=rand()%(u-l+1)+l;
		sprintf(buff,"%lu",r);
		lookupSmartBF(buff);
	}
	end=clock();
	//fp=(double)(found)/(double)n;
	fp=(double)(TP)/(double)(n);
	diff=(double)(end-start)/CLOCKS_PER_SEC;
	printf("\nDisjoint set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100.0,fp);
	printf("Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	fprintf(f,"\nDisjoint set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100.0,fp);
	//fprintf(f,"Millions insertion:%lf\n",(double)n/diff);
	fprintf(f,"Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	
	printf("Summary:\n");
	printf("TP: %lu\tTN:  %lu\n",TP,TN);
	fprintf(f,"Summary:\n");
	fprintf(f,"TP: %lu\tTN:  %lu\n",TP,TN);
	
	TP=0;TN=0;

	///////////////////////
	//Random set
	///////////////////////
	start=clock();
	i=0;fp=0.0;
	for(i=1;i<=n;i++)
	{
		r=rand();
		if(r<=n)
			count++;
		sprintf(buff,"%lu",r);
		lookupSmartBF(buff);
	}
	end=clock();
	//fp=(double)(found-count)/(double)n;
	fp=(double)(TP-count)/(double)(n);
	diff=(double)(end-start)/CLOCKS_PER_SEC;
	
	printf("\nRandom set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100.0,fp);
	printf("Count:%lu\n",count);
	printf("Elapsed Time of lookup:%f\n",(double)(end-start)/CLOCKS_PER_SEC);
	fprintf(f,"\nRandom set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100.0,fp);
	//fprintf(f,"Millions insertion:%lf\n",(double)n/diff);
	fprintf(f,"Elapsed Time of lookup:%f\n",(double)(end-start)/CLOCKS_PER_SEC);

	printf("Summary:\n");
	printf("TP: %lu\tTN:  %lu\n",TP,TN);
	fprintf(f,"Summary:\n");
	fprintf(f,"TP: %lu\tTN:  %lu\n",TP,TN);
	
	TP=0;TN=0;

	double mb=8*1024*1024.0;
	//unsigned long int s=size;
	printf("\nRequired memory size in bits: %lu\n", size);
	printf("\nTotal memory size in MB: %lf\n", (double)(size)/mb);
	fprintf(f,"\nTotal memory size in MB: %lf\n", (double)(size)/mb);

	printf("\nRequired memory size in bits: %lu\n", m);
	printf("\nRequired memory size in MB: %lf\n", (double)(m)/mb);
	fprintf(f,"\nRequired memory size in MB: %lf\n",(double)(m)/mb);

	/*double gb=8*1024*1024*1024.0;
	printf("Total memory size in GB: %lf\n", (double)(size)/gb);
	fprintf(f,"Total memory size in GB: %lf\n", (double)(size)/gb);*/


	freeSmartBF();
	fclose(f);
	return 0;
}
