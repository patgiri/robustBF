
unsigned long int size=0;
static int seed1, seed2,seed3,seed4,seed5;//,seed6, seed7, seed8,seed9,seed10;
//static int seed11, seed12,seed13,seed14,seed15,seed16, seed17, seed18,seed19,seed20;
unsigned long int selectPrime(unsigned long int k)
{
	unsigned long int i;
	for(i=1;i<total_prime;i++)
	{
		if(prime[i]>k)
			return i;
	}
}

void initSeed()
{
	seed1=7689571;
	seed2=15485863;
	seed3=98899;
	seed4=71287;
	seed5=101653;
	/*seed6=7523;
	seed7=10007;
	seed8=prime[2701];
	seed9=prime[1901];
	seed10=prime[9901];
	seed11=prime[6601];
	seed12=prime[7721];
	seed13=prime[1101];
	seed14=prime[1001];
	seed15=prime[6501];
	seed16=prime[7501];
	seed17=prime[8801];
	seed18=prime[1701];
	seed19=prime[1801];
	seed20=prime[5901];*/
}

double error(unsigned long int m, unsigned long int n)
{
	return pow((1-exp(-2*n/m)),2);
}
unsigned long int memory(unsigned long int n, double err)
{
	return (unsigned long int)(-(n*log(err))/pow(log(2),2));
}
unsigned long int number(unsigned long int m,double err)
{
	return (unsigned long int)(-(m*pow(log(2),2))/log(err));
}

void setDim(unsigned long int m)
{
	unsigned long int k=m/(2*64); 
	int a,b,c,d,e,f;
	unsigned long int i;

	f=sqrt(k);
	i=selectPrime(f);
	//int j=(i/1.5);
	a=prime[i/2+3];
	b=prime[i/2-3];
	//c=prime[i-3];
	//d=prime[i+3];
	//e=prime[i/3+3];
	//f=prime[i/3-3];
	dim(a,b);
	//dim1(c,d);
	//dim2(e,f);
	 
	printf("2DBF dimensions: \n%d  %d\n",a,b);
	size+=(a*b)*64;

}
