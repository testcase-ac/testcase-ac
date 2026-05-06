#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,r=0;
    cin>>n;
    for(int i=0;i*i<=n;i++) for(int j=0;i*i+j*j<=n;j++) for(int k=0;i*i+j*j+k*k<=n;k++) {
        int t=n-i*i-j*j-k*k,s=sqrt(t);
        if(s*s==t) r++;
    } cout<<r;
}
