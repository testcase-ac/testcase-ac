#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin>>n;
    if(n%2) {cout<<1;return 0;}
    int v[n];
	for(int i=0;i<n;i++) {
		int a,b;
		cin>>a>>b;
		v[i]=a-b;
	} sort(v,v+n);
	cout<<v[n/2]-v[n/2-1]+1;
}
