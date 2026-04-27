#include<iostream>
using namespace std;
int m,n,d[2010][2010],out;
char line[2010];
inline int mx2(int a,int b)
{
	if(a>b)return a;
	return b;
}
int main()
{
	int i,j,mx;
	cin>>m>>n;
	for(i=1;i<=m;++i)
	{
	    cin>>line+1;
	    for(j=1;j<=n;++j)d[i][j]=line[j]-'0';
	}
	for(j=2;j<=n;++j)
	{
		for(i=1;i<=m;++i)
		{
			mx=d[i][j-1];
			if(i>1)mx=mx2(mx,d[i-1][j-1]);
			if(i<m)mx=mx2(mx,d[i+1][j-1]);
			out=mx2(out,mx);
			d[i][j]=d[i][j]+mx;
		}
	}
	cout<<out;
	return 0;
}
