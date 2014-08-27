#include<stdio.h>
#include<math.h>
#include<time.h>

#define min -1000000009
#define max 1000000009 
long long int que;
int compare(int *a,int *b)
{
	return *a-*b;
}

typedef struct segment
{
	int lower;
	int upper;
}segment;

typedef struct node
{
	segment range;
	int h;	
}node;

segment inp[10000];
int j,t,no_inp;
int end_pts[10000];
int end_pts2[10000];
node tree[10000];

void maketree(int *end_pts,int len)
{
	if(len==2)
	{
		tree[t].h = 0;
		tree[t].range.lower = end_pts[0];
		tree[t++].range.upper = end_pts[1];
		return;
	}
	int temp[10000];
	int i;

	for(i=0;i<len;i+=2)
	{
		temp[i/2] = end_pts[i];
	}

	maketree(temp,len/2+1);

	for(i=0;i<len-1;i++)
	{
		tree[t].h = 0;
		tree[t].range.lower = end_pts[i];
		tree[t++].range.upper = end_pts[i+1];
	}
}

void insert_tree(int v,int low,int up)
{
	if(tree[v].range.lower>up || tree[v].range.upper<low)
	{
		return;
	}

	int lc = 2*v;
	int rc = 2*v + 1;

	if(tree[v].range.lower>=low && tree[v].range.upper<=up)	
	{
		tree[v].h++;
	}
	else 
	{
		if(lc >= t/2)
		{
			if(low<tree[lc].range.upper && up>tree[lc].range.lower)
			{
				insert_tree(lc,low,up);
			}
			if(low==tree[rc].range.upper || up==tree[rc].range.lower)
			{
				insert_tree(rc,low,up);
			}
		}
		else
		{
			if(low<=tree[lc].range.upper && up>tree[lc].range.lower)
			{
				insert_tree(lc,low,up);
			}
			if(low<=tree[rc].range.upper && up>tree[rc].range.lower)
			{
				insert_tree(rc,low,up);
			}
		}
	}
}

void query(int v,int q)
{
	int i,h,lc,rc;
	h = tree[v].h;

	que+=h;

	if(v < t/2)
	{
		lc = 2*v;
		rc = 2*v + 1;

		if(lc >= t/2)
		{
			if(q>tree[lc].range.lower && q<tree[lc].range.upper)
			{
				query(lc,q);
			}
			else
			{
				query(rc,q);
			}
		}
		else
		{
			if(q>tree[lc].range.lower && q<=tree[lc].range.upper)
			{
				query(lc,q);
			}
			else
			{
				query(rc,q);
			}
		}
	}
}

int main()
{
	int seg,i=0,x,k;

	scanf("%d",&seg);
	FILE *f1;
	f1=fopen("t1.txt","a");
	end_pts[0] = min;
	while(seg--)
	{
		scanf("%d %d",&inp[i++].lower,&inp[i].upper);
		end_pts[++j] = inp[i-1].lower;
		end_pts[++j] = inp[i-1].upper;
		if(inp[i-1].lower>inp[i-1].upper)
		{
			int temp=inp[i-1].lower;
			inp[i-1].lower=inp[i-1].upper;
			inp[i-1].upper=temp;
		}
	}
	no_inp = i;

	qsort(end_pts,j+1,sizeof(int),compare);

	k = 0;
	for(i=0;i<=j;i++)		
	{
		end_pts2[k] = end_pts[i];
		while(end_pts[i+1]==end_pts2[k])
			i++;
		k++;
	}

	j = k;

	x = 1;
	while(x<j)			
		x=x<<1;
	while(j<=x)
		end_pts2[j++] = max;

	t = 1;
	maketree(end_pts2,j);
	for(i=0;i<j-1;i++)
	{
		tree[t].range.lower = end_pts2[i];
		tree[t++].range.upper = end_pts2[i+1];

		tree[t].range.lower = end_pts2[i+1];
		tree[t++].range.upper = end_pts2[i+1];
	}

	for(i=0;i<no_inp;i++)
	{
		insert_tree(1,inp[i].lower,inp[i].upper);
	}

	int q,z,num_que;
	scanf("%d",&z);
	num_que = z;
	
	clock_t t1,t2;
	t1=clock();
	
	while(z--)
	{
		que=0;
		scanf("%d",&q);
		printf("query : %d\n",q);
		query(1,q);
		printf("Ans : %lld\n",que);
	}
	t2=clock();
	
	int time=(t2-t1)/CLOCKS_PER_SEC;
	fprintf(f1,"%d %d\n",num_que,time);
	
	return 0;
}
