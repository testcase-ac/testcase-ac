#include <bits/stdc++.h>
#define lll __int128
#define ll long long
using namespace std;
const lll MOD=10000000000;
void mult(lll F[2][2],lll M[2][2]) {
    lll x,y,z,w;
    x=(F[0][0]*M[0][0]+F[0][1]*M[1][0])%MOD;
    y=(F[0][0]*M[0][1]+F[0][1]*M[1][1])%MOD;
    z=(F[1][0]*M[0][0]+F[1][1]*M[1][0])%MOD;
    w=(F[1][0]*M[0][1]+F[1][1]*M[1][1])%MOD;
    F[0][0]=x;
    F[0][1]=y;
    F[1][0]=z;
    F[1][1]=w;
}
void pw(lll F[2][2],ll n) {
    lll M[2][2]={{1,1},{1,0}};
    while(n) {
        if(n%2) mult(F,M);
        mult(M,M);
        n/=2;
    }
}
ll fibo(ll n) {
    if(n==0) return 0;
    if(n==1) return 1;
    lll F[2][2]={{1,1},{1,0}};
    pw(F,n-1);
    return (ll)F[0][0];
}
lll power(lll a,lll n,lll m) {
    lll r=1;
    while(n) {
        if(n%2) r=r*a%m;
        a=a*a%m;
        n/=2;
    } return r;
}
int main() {
    int t;
    ll a;
    lll n;
    cin>>t;
    while(t--) {
        cin>>a;
        n=a;
        n=power(7,n,1600000000);
        n=power(7,n,4000000000);
        n=power(7,n,15000000000);
        a=fibo(n-1);
        string s=to_string(a);
        while(s.length()<10) s='0'+s;
        cout<<s<<'\n';
    }
}
