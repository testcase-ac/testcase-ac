#include <bits/stdc++.h>
#define ll __int128
using namespace std;
const ll M=(ll)1e18+(ll)14e9+49;
const ll P=1e9+7;
void mult(ll F[2][2],ll A[2][2]) {
    ll x,y,z,w;
    x=(F[0][0]*A[0][0]+F[0][1]*A[1][0])%M;
    y=(F[0][0]*A[0][1]+F[0][1]*A[1][1])%M;
    z=(F[1][0]*A[0][0]+F[1][1]*A[1][0])%M;
    w=(F[1][0]*A[0][1]+F[1][1]*A[1][1])%M;
    F[0][0]=x;
    F[0][1]=y;
    F[1][0]=z;
    F[1][1]=w;
}
void pw(ll F[2][2],ll n) {
    ll A[2][2]={{1,1},{1,0}};
    while(n>0) {
        if(n%2) mult(F,A);
        mult(A,A);
        n/=2;
    }
}
ll fibo(ll n) {
    if(n==-1||n==1) return 1;
    if(n==0) return 0;
    ll F[2][2]={{1,1},{1,0}};
    pw(F,n-2);
    return F[0][0];
}
ll ipw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%P;
        a=a*a%P;
        n/=2;
    } return r;
}
int main() {
    long N,K;
    ll n,k;
    cin>>N>>K;
    n=N;k=K;
    ll ff=fibo(n*k),f=fibo(k);
    if(f%P==0) {ff/=P;f/=P;}
    ll A=ff*ipw(f,P-2)%P;
    ll B=fibo(n*k-1)%P-A*fibo(k-1)%P;
    if(B<0) B+=P;
    cout<<(long)A<<' '<<(long)B;
}
