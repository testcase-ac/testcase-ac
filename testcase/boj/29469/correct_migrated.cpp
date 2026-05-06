#include <bits/stdc++.h>
using namespace std;
map<int,int> mp;
long vpf(long n,int p) {
    long r=0;
    while(n) {
        n/=p;
        r+=n;
    } return r;
}
int main() {
    long n;
    int k;
    cin>>n>>k;
    for(int i=2;i*i<=k;i++) {
        while(k%i==0) {
            k/=i;
            mp[i]++;
        }
    } if(k>1) mp[k]++;
    long z=1e18;
    for(auto [p,e]:mp) {
        z=min(z,vpf(n,p)/e);
    } cout<<z;
}
