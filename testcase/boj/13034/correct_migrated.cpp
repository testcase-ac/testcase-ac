#include <bits/stdc++.h>
using namespace std;
int main() {
	int n,g[1001];
	g[0]=g[1]=0;
	g[2]=1;
	bool b[1001];
	for(int i=3;i<1001;i++) {
	    memset(b,0,1001);
	    for(int j=0;j<i/2+1;j++) b[g[j]^g[i-j-2]]=1;
	    for(int j=0;j<i;j++) if(!b[j]) {g[i]=j;break;}
	} cin>>n;
	cout<<(g[n]?1:2);
}
