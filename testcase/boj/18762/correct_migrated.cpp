#include <bits/stdc++.h>
using namespace std;
int k=1;
int irr[13]={0,3,7,11,25,41,97,145,433,601,1531,3005,5703};
struct GF {
    int n,k;
    GF operator+(const GF&x) const {return {n^x.n,k};}
    GF operator*(const GF&x) const {
        int r=0,a=n,b=x.n,ir=irr[k];
        while(a*b!=0) {
            if(b%2) r^=a;
            if(a&(1<<k-1)) a=a*2^ir;
            else a*=2;
            b/=2;
        } return {r,k};
    }
};
int main() {
    int n;
    cin>>n;
    while((1<<k*2+1)<n) k++;
    GF z;
    z.n=1<<k;z.k=k;
    int s=int(sqrt(n*0.5));
    if(s==1) {cout<<"1\n1";return 0;}
    else if(s==2) {cout<<"2\n1 2";return 0;}
    cout<<s<<'\n';
    for(int i=0;i<s;i++) {
        GF x,r;
        x.n=i;x.k=k;
        r=z*x+x*x*x;
        cout<<(r.n^1)<<' ';
    }
}
