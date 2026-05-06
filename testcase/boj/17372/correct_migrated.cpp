#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
ll phi[1000001];
map<ll,ll> phi2;
void mult(ll A[2][2],ll B[2][2]) {
	ll x=(A[0][0]*B[0][0]+A[0][1]*B[1][0])%M;
	ll y=(A[0][0]*B[0][1]+A[0][1]*B[1][1])%M;
	ll z=(A[1][0]*B[0][0]+A[1][1]*B[1][0])%M;
	ll w=(A[1][0]*B[0][1]+A[1][1]*B[1][1])%M;
	A[0][0]=x;A[0][1]=y;A[1][0]=z;A[1][1]=w;
}
void pw(ll F[2][2],ll n) {
    ll X[2][2]={{1,1},{1,0}};
    while(n>0) {
        if(n%2) mult(F,X);
        mult(X,X);
        n/=2;
    }
}
ll fibo(ll n) {
    ll F[2][2]={{1,1},{1,0}};
    pw(F,n);
    return F[0][0];
}
ll ph(ll n) {
	if(n<1000001) return phi[n];
	if(phi2.find(n)!=phi2.end()) return phi2[n];
	ll r=n*(n+1)/2;
	for(ll i=2,j;i<=n;i=j+1) {
		j=n/(n/i);
		r-=(j-i+1)*ph(n/i);
	} return phi2[n]=r;
}
int main() {
	for(int i=1;i<1000001;i++) phi[i]=i;
	for(int i=2;i<1000001;i++) {
        if(phi[i]==i) for(int j=i;j<1000001;j+=i) phi[j]-=phi[j]/i;
    } for(int i=1;i<1000001;i++) {phi[i]+=phi[i-1];if(phi[i]>M) phi[i]-=M;}
	ll n;
	cin>>n;
	ll s=(ph(n)*2-1)%M;
	for(ll i=2,l,r=1;i<=n;i=r+1) {
		l=r;
		r=n/(n/i);
		ll x=(fibo(r)-fibo(l))%M,y=(ph(n/i)*2-1)%M;
		s=(s+x*y%M+M)%M;
	} cout<<s;
}
