#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
	int e1;
	int e2;
	int lr;
}node;


typedef struct node1
{
	node med;
	int ml,mr;
	node aux_l[500];
	node aux_r[500];

}node1;

int compare(const void* a,const void *b)
{
	node* c = (node*)a;
	node* d = (node*)b;

	return ((c->e1) - (d->e1));
}

node inp[100000];
int tr_no;
node1 tree[100000];

int end_tr;
int count;

node left[10000],right[10000];

void maketree(node *inp,int h,int end)
{

	if(h==0)
	{
		tree[end].med.e1=10000;
		tree[end].med.e2=10000;
		tree[end].med.lr=-1;
	printf("%d %d %d %d\n",tree[end].med.e1,tree[end].med.e2,tree[end].ml,tree[end].mr);
		return;
	}
	int i;	
	if(end_tr<end)
		end_tr=end;

	tree[end].med=inp[h/2];

	int l,r,ml,mr;

	l=r=ml=mr=0;


	for(i=0;i<h;i++)
	{

		if((inp[i].e2<tree[end].med.e1 && inp[i].lr==0) || (inp[i].e1<tree[end].med.e1 && inp[i].lr==1))
			left[l++]=inp[i];
		else if((inp[i].e1>tree[end].med.e1 && inp[i].lr==0) || (inp[i].e2>tree[end].med.e1 && inp[i].lr==1))
			right[r++]=inp[i];
		else
		{
			if(inp[i].lr==0)
				tree[end].aux_l[ml++]=inp[i];
			else
				tree[end].aux_r[mr++]=inp[i];
		}

	}

	tree[end].ml=ml;
	tree[end].mr=mr;
	printf("%d %d %d %d\n",tree[end].med.e1,tree[end].med.e2,tree[end].ml,tree[end].mr);
	fflush(0);
	maketree(left,l,2*end);
	maketree(right,r,2*end+1);
}

void query(int q,int v)
{
	if(tree[v].med.e1 == 10000)
	{
		return;
	}
	
	int i;
	if(q == tree[v].med.e1)
	{
		count += tree[v].ml;
		return;
	}
	else if(q < tree[v].med.e1)
	{
		query(q,2*v);
		for(i=0;i<tree[v].ml;i++)
		{
			if(tree[v].aux_l[i].e1 > q)
				break;
			count++;
		}
	}
	else if(q > tree[v].med.e1)
	{
		query(q,2*v+1);
		for(i=tree[v].mr-1;i>=0;i--)
		{
			if(tree[v].aux_r[i].e1 < q)
				break;
			count++;
		}
	}
}

int main()
{
	int seg,i,h;
	h=0;

	FILE* f1;
	f1 = fopen("t_int.txt","a");

	scanf("%d",&seg);
	while(seg--)
	{
		scanf("%d %d",&inp[h].e1,&inp[h].e2);
		if(inp[h].e1>inp[h].e2)
		{
			int tmp=inp[h].e1;
			inp[h].e1=inp[h].e2;
			inp[h].e2=tmp;
		}
		
		inp[h++].lr = 0;


		inp[h].e1 = inp[h-1].e2;
		inp[h].e2 = inp[h-1].e1;
		inp[h++].lr = 1;
	}

	qsort(inp,h,sizeof(node),compare);

	maketree(inp,h,1);

//	printf("\n\n");
//	for(i=1;i<=end_tr;i++)

	int q,z,num_que;
	scanf("%d",&z);
	num_que = z;

	clock_t t1,t2;
	t1 = clock();

	while(z--)
	{
		count = 0;

		scanf("%d",&q);
		printf("query : %d\n",q);
		query(q,1);
		printf("Ans : %d\n",count);
	}
	t2 = clock();

	float time = (t2-t1)/CLOCKS_PER_SEC;
	fprintf(f1,"%d %f\n",num_que,time);

	return 0;
}
