#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
int main() {
	ll n,m,r=1;
	cin>>n>>m;
	int x=min(n,m);
	vector<int> p(x+1,0);
	for(int i=2;i*i<=x;i++) if(p[i]==0) for(int j=i*i;j<=x;j+=i) p[j]=i;
	for(ll i=2;i<=x;i++) {
	    ll t=i;
	    if(p[i]) {
            while(t%p[i]==0) t/=p[i];
            if(t>1) continue;
            t=p[i];
        } r=r*pw(t,(n/i)*(m/i))%M;
	} cout<<r;
}
