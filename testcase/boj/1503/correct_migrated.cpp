#include <bits/stdc++.h>
using namespace std;
int x[1002];
int main() {
    int n,m,a,r=2e9;
    cin>>n>>m;
    while(m--) {
        cin>>a;
        x[a]=1;
    } for(int i=1;i<=1001;i++) {
        if(x[i]) continue;
        for(int j=i;j<=1001;j++) {
            if(x[j]) continue;
            for(int k=j;k<=1001;k++) {
                if(x[k]) continue;
                r=min(r,abs(n-i*j*k));
            }
        }
    } cout<<r;
}
