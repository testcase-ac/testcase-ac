#include <stdio.h>
#define M 15
int n,a,b;
int p[M], q[M];
int mark[105][105];
int as[105][105][M];
void mul(int* r,int *s)
{
	int t[M];
	int i, j;
	for(i=0; i<M; i++)
		t[i] = 0;
	for(i=0; i<M; i++)
	{
		for(j=0; j<M; j++)
		{
			if(i+j<M)
			{
				t[i+j] += r[i]*s[j];
			}
		}
	}
	for(i=0; i<M-1; i++)
	{
		if(t[i] > 9)
		{
			t[i+1] += t[i]/10;
			t[i] %= 10;
		}
	}
	t[M-1] %= 10;

	for(i=0; i<M; i++)
		r[i] = t[i];
}
void PRINT(int* r)
{
	int i;
	for(i=n-1; i>=0; i--)
		printf("%d",r[i]);
	for(i=0; i<M; i++)
		as[b][a][i] = r[i];
	mark[b][a]=1;
	printf("\n");
}
void exp(int* r,int x,int* y)
{
	int i, j;
	int s[M];
	for(i=0; i<M; i++)
	{
		r[i] = 0;
		s[i] = 0;
	}
	r[0] = 1;
	s[0] = x;
	i = 0;
	while(i<M && s[i]>9){s[i+1]+=(s[i]/10); s[i]%=10; i++;}
	while(1)
	{
		for(i=0; i<M; i++)
			if(y[i])break;
		if(i==M)break;
		if(y[0]%2)
		{
			mul(r,s);
		}
		mul(s,s);
		j=0;
		for(i=M-1; i>=0; i--)
		{
			j*=10;
			j+=y[i];
			y[i]=j/2;
			j%=2;
		}
	}
}
void process()
{
	int i, j;
	for(i=0; i<M; i++)
		p[i] = 0;
	p[0] = 1;

	for(i=0; i<a; i++)
	{
		exp(q, b, p);
		for(j=0; j<M; j++)
			p[j] = q[j];
	}
	PRINT(p);
}
void process_1()
{
	long long int r;
	if(a == 1)
	{
		int i;
		int s[M];
		for(i=0; i<M; i++)
			s[i] = 0;
		s[0] = b;
		i=0;
		while(i<M && s[i]>9)
		{
			s[i+1] += s[i]/10;
			s[i]%=10;
			i++;
		}
		PRINT(s);
	}
	else{
		for(int i=0; i<n; i++)
		{
			as[b][a][i] = 0;
			printf("0");
		}
		printf("\n");
		mark[b][a] = 1;
		
	}
}
int main()
{
	b=n=a=1;
	while(1)
	{
		scanf("%d",&b);
		if(b==0)break;
		scanf("%d %d",&a,&n);
		if(a>9)a = 9;
		if(mark[b][a])
		{
			for(int i=n-1; i>=0; i--)
				printf("%d",as[b][a][i]);
			printf("\n");
			continue;
		}
		if(b%10)
		{
			process();
		}
		else
		{
			process_1();
		}
//		n++;
//		if(n>7){a++;n=1;}
//		if(a>100){b++;a=1;}
	}
}
