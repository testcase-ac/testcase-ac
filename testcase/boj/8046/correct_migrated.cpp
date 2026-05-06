#include <bits/stdc++.h>
using namespace std;
vector<int> cyc(const vector<int>&p) {
    vector<int> cyc,v(p.size(),0);
    for(int i=0;i<p.size();i++) {
	    if(v[i]) continue;
		int c=0,x=i;
		while(!v[x]) {v[x]=1;c++;x=p[x];}
		cyc.push_back(c);
	} return cyc;
}
int main() {
    int n;
    cin>>n;
    vector<int> a(n);
    int t=0,r=1;
    for(int i=0;i<n;i++) {cin>>a[i];a[i]--;}
    auto v=cyc(a);
    for(int i:v) {
        if(i%2==0) {cout<<0;return 0;}
        t+=i/2;
    } for(int i=0;i<v.size();i++) for(int j=i+1;j<v.size();j++) t+=gcd(v[i],v[j]);
    while(t--) r=r*2%1000;
    cout<<r;
}
