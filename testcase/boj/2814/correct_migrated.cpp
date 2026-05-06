#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n,p;
    cin>>n>>p;
    if(p==2) {
        long long r=n*2;
        if(r>1e9) cout<<0;
        else cout<<r;
    } else if(p==3) {
        long long r=n*6-3;
        if(r>1e9) cout<<0;
        else cout<<r;
    } else if(p==5) {
        long long r;
        if(n%2) r=(n-1)*15+5;
        else r=n*15-5;
        if(r>1e9) cout<<0;
        else cout<<r;
    } else if(p==7) {
        long long r,a[8]={7,49,77,91,119,133,161,203};
        r=((n-1)/8)*210+a[(n-1)%8];
        if(r>1e9) cout<<0;
        else cout<<r;
    } else {
        int z=1000000000/p;
        vector<bool> v(z+1,1);
        for(int i=2;i<p;i++) if(v[i]) for(int j=i;j<=z;j+=i) v[j]=0;
        for(int i=1;i<=z;i++) {
            if(v[i]) {
                n--;
                if(!n) {cout<<p*i;return 0;}
            }
        } cout<<0;
    }
}
