#include<stdio.h>
#include<stdlib.h>

int main()
{
	int x=rand()%1000;
	printf("%d\n",x);
	int i;
	for(i=0;i<x;i++)
	{
		int c=rand()%100;
		int d=rand()%100;
		int a=rand()%(1000);
		int b=rand()%(1000);
		
		if(c%2==0)
			a=a*-1;
		if(d%2==0)
			b=b*-1;
		printf("%d %d\n",a,b);
	}
	
	long long int y=2000000;		//multiple data sets by changing y
	printf("%lld\n",y);
	for(i=0;i<y;i++)
	{
		int a=rand()%1000;
		printf("%d\n",a);
	}
return 0;
}
