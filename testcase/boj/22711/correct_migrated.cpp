#include <bits/stdc++.h>
#define ll long long
using namespace std;
pair<ll,ll> pell(ll d) {
	ll a0=sqrt(d);
	ll m=0,c=1,a=a0;
	ll p0=1,p1=a,q0=0,q1=1;
	if(a0*a0==d) return {0,0};
	while(p1*p1-d*q1*q1!=1) {
		m=c*a-m;
		c=(d-m*m)/c;
		a=(a0+m)/c;
		ll p2=a*p1+p0;
		ll q2=a*q1+q0;
		p0=p1;p1=p2;
		q0=q1;q1=q2;
	} return {p1,q1};
}
int main() {
    int t=0;
    ll n;
    while(1) {
        cin>>n;
        if(!n) return 0;
        t++;
        n*=2;
        cout<<"Case "<<t<<": ";
        ll s=sqrt(n);
        if(s*s==n) {
            cout<<s<<" 1\n";
            continue;
        } auto [a,b]=pell(n);
        cout<<a<<' '<<b<<'\n';
    }
}
