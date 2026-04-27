#include<iostream>
using namespace std;
int n,m,a,b;
int main()
{
	int i,x,y;
	cin>>n>>m;
	a=n;
	b=n;
	for(i=1;i<=m;++i)
	{
		cin>>x>>y;
		if(x>=b||y>=a)continue;
		if(a*x>=b*y)b=x;
		else a=y;
	}
	cout<<a*b;
	return 0;
}
