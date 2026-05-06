#include <bits/stdc++.h>
#define ll long long
#define lll __int128
using namespace std;
const lll MOD=1e13;
void mult(lll A[2][2],lll B[2][2],lll M) {
	lll x=(A[0][0]*B[0][0]+A[0][1]*B[1][0])%M;
	lll y=(A[0][0]*B[0][1]+A[0][1]*B[1][1])%M;
	lll z=(A[1][0]*B[0][0]+A[1][1]*B[1][0])%M;
	lll w=(A[1][0]*B[0][1]+A[1][1]*B[1][1])%M;
	A[0][0]=x;A[0][1]=y;A[1][0]=z;A[1][1]=w;
}
void pw(lll F[2][2],lll n,lll M) {
    lll X[2][2]={{1,1},{1,0}};
    while(n>0) {
        if(n%2) mult(F,X,M);
        mult(X,X,M);
        n/=2;
    }
}
lll fibo(lll n,lll M) {
    if(n==0) return 0;
    lll F[2][2]={{1,1},{1,0}};
    pw(F,n-2,M);
    return F[0][0];
}
int main() {
    ll n;
    cin>>n;
    if(n==MOD) {cout<<-1;return 0;}
    vector<lll> v;
    for(lll i=0;i<1500;i++) if(fibo(i,1000)==n%1000) v.push_back(i);
    for(lll i=10000;i<=10000000000000;i*=10) {
        vector<lll> t;
        for(lll j:v) {
            for(lll k=0;k<10;k++) if(fibo(j+k*i*3/20,i)==n%i) t.push_back(j+k*i*3/20);
        } v=t;
    } sort(v.begin(),v.end());
    if(v.empty()) cout<<-1;
    else cout<<(ll)v[0];
}
