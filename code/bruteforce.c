#include <stdio.h>
#include <time.h>

typedef struct segment
{
	int lower;
	int upper;
}segment;

segment inp[10000];
int no_inp;

int query(int q)
{
	int i,count = 0;
	for(i=0;i<no_inp;i++)
	{
		if(q>=inp[i].lower && q<=inp[i].upper)
		{
			count++;
		}
	}

	return count;
}

int main()
{
	int seg,tmp,z,q,i=0;

	FILE *f1;
	f1 = fopen("t_brute.txt","a");

	scanf("%d",&seg);
	while(seg--)
	{
		scanf("%d %d",&inp[i++].lower,&inp[i].upper);
		if(inp[i-1].lower > inp[i-1].upper)
		{
			tmp = inp[i-1].lower;
			inp[i-1].lower = inp[i-1].upper;
			inp[i-1].upper = tmp;
		}
	}
	no_inp = i;

	scanf("%d",&z);
	int num_que = z;

	clock_t t1,t2;
	t1 = clock();

	while(z--)
	{
		scanf("%d",&q);
		printf("query : %d\n",q);
		printf("Ans : %d\n",query(q));
	}
	t2 = clock();

	int time = (t2-t1)/CLOCKS_PER_SEC;
	fprintf(f1,"%d %d\n",num_que,time);

	return 0;
}
