#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n,k;
    cin>>n>>k;
    k=n-k+1;
    double r=0;
    while(k<=1000000&&k<=n) {
        r+=1.0/k;
        k++;
    } if(k<=n) r+=log1p(2.0*(n-k+1)/(k*2-1));
    cout<<fixed<<setprecision(15)<<r*n;
}
