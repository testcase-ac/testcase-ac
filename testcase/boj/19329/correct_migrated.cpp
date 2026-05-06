#include <bits/stdc++.h>
using namespace std;
int main() {
    random_device rd;
	mt19937_64 g(rd());
    int n,k;
    cin>>n>>k;
    vector<long long> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    long long mx=0,d;
    for(int i=0;i<1000;i++) {
        shuffle(a.begin(),a.end(),g);
        d=a[0];
        int t=0;
        bool f=1;
        for(int i=1;i<n;i++) {
            long long x=gcd(d,a[i]);
            if(x<=mx) {
                t++;
                if(t==k+1) {f=0;break;}
            } else d=x;
        } if(f) mx=max(mx,d);
    } cout<<mx;
}
