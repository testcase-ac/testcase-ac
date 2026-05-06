#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n,m,r,t;
    cin>>n>>m;
    m-=n;
    r=(n+1)*(n+1)*4+(n*4+4)*(n*4+3)+n*(n+1)*(n+2)/6*25;
    while(m) {
        t=min(m,n);
        m-=t;
        r-=t*(t+1);
    } cout<<r-m*2;
}
