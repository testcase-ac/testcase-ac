#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll phi(ll n) {
    ll r=n;
    for(ll i=2;i*i<=n;i++) {
        if(n%i==0) {
            r=r/i*(i-1);
            while(n%i==0) n=n/i;
        }
    } if(n>1) r=r/n*(n-1);
    return r;
}
ll pw(ll a,ll n,ll m) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%m;
        a=a*a%m;
        n/=2;
    } return r;
}
int main() {
    ll t,a,b,c;
    cin>>t;
    for(int i=1;i<=t;i++) {
        cin>>a>>b>>c;
        ll p[1001],x[1001];
        ll t=c;
        while(t>1) {p[t]=phi(t);t=p[t];}
        t=c;
        while(t>1) {x[t]=pw(a,a,t);t=p[t];}
	    while(--b) {
		    t=c;
		    while(t>1) {
		    	x[t]=pw(x[t],x[p[t]]?x[p[t]]:x[p[t]]+p[t],t);
			    t=p[t];
		    }
        } cout<<"Case #"<<i<<": "<<x[c]<<'\n';
    }
}
