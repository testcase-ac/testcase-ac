#include <stdio.h>
#include <vector>
#include <numeric>
// #include "hat.h"
using namespace std;

static int n,te,p;

void init(int N)
{
	// Do Something...
}

int call(vector<int> F, vector<int> B, int num)
{
	int n = F.size();
	if (num == n - 1) return accumulate(F.begin(), F.end(), 0) % 64;
	else {
		int s = B[n - 1];
		int b = accumulate(B.begin() + num + 1, B.end() - 1, 0);
		int f = accumulate(F.begin(), F.begin() + num, 0);
		return (B[n - 1] + 64 - ((b + f) % 64)) % 64;
	}
}

int main()
{
	scanf("%d%d",&n,&te);
	init(n);
	for(int tn=0;tn<te;tn++)
	{
		vector<int> F(n),B(n),OF(n);
		for(int i=0;i<n-1;i++)
			scanf("%d",&F[i]);
		bool check=true;
		for(int i=n-1;i>=0;i--)
		{
			int nans=F[i];
			F[i]=0;
			int c=call(F,B,i);
			B[i]=c;
			if(c<0 || c>63 || (i!=n-1 && nans!=c))
			{
				check=false;
				break;
			}
		}
		if(check) printf("1\n");
		else printf("0\n");
	}
}