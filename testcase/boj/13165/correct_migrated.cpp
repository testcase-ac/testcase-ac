#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main() {
    cin.tie(0);
    random_device rd;
	mt19937_64 g(rd());
	int n,l,k=0;
	cin>>n>>l;
	ll a[n][l],x[n],y[n],z[n],r[n];
	for(int i=0;i<n;i++) r[i]=g()%7676767;
	for(int i=0;i<n;i++) for(int j=0;j<l;j++) cin>>a[i][j];
	for(int t=0;t<=l-n*3;t++) {
	    for(int i=0;i<n;i++) {
	        x[i]=0;
	        for(int j=0;j<n;j++) x[i]+=a[i][t+j+n]*r[j];
	    } for(int i=0;i<n;i++) {
	        y[i]=0;
	        for(int j=0;j<n;j++) y[i]+=a[i][t+j]*x[j];
	    } for(int i=0;i<n;i++) {
	        z[i]=0;
	        for(int j=0;j<n;j++) z[i]+=a[i][t+j+n*2]*r[j];
	    } bool f=1;
	    for(int i=0;i<n;i++) if(y[i]!=z[i]) {f=0;break;}
	    if(f) {k++;t+=n*3-1;}
	} cout<<k*n*n*3;
}
