#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
void mult(ll A[2][2],ll B[2][2]) {
	ll x=(A[0][0]*B[0][0]+A[0][1]*B[1][0])%M;
	ll y=(A[0][0]*B[0][1]+A[0][1]*B[1][1])%M;
	ll z=(A[1][0]*B[0][0]+A[1][1]*B[1][0])%M;
	ll w=(A[1][0]*B[0][1]+A[1][1]*B[1][1])%M;
	A[0][0]=x;A[0][1]=y;A[1][0]=z;A[1][1]=w;
}
void pw(ll F[2][2],ll n) {
    ll X[2][2]={{1,M-1},{4,1}};
    while(n>0) {
        if(n%2) mult(F,X);
        mult(X,X);
        n/=2;
    }
}
ll cn(ll n) {
    ll F[2][2]={{1,0},{0,1}};
    pw(F,n);
    return F[1][1];
}
ll ipw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	int q;
	ll i,j,k;
	cin>>q;
	while(q--) {
	    cin>>i>>j>>k;
	    ll ck=cn(k),cki=cn(k*i),ckj=cn(k*j),cki1=cn(k*(i-1)),ckj1=cn(k*(j+1));
	    cout<<((ipw(5,k)*(ckj-cki1)%M-ckj1+cki)*ipw((ipw(5,k)-ck*2+1+M)%M,M-2)%M+M)%M<<'\n';
	}
}
