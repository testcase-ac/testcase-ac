#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
const ll MAX=5e7;
bool isp[MAX+1];
vector<ll> p;
vector<ll> mu(MAX+1,0);
unordered_map<ll,ll> mu2;
ll getmu(ll n) {
	if(n<=MAX) return mu[n];
	unordered_map<ll,ll>::iterator x=mu2.find(n);
	if(x!=mu2.end()) return x->second;
	ll r=1;
	for(ll i=2,j;i<=n;) {
		j=n/(n/i);
		r+=M-(j%M*(j%M+1)/2-i%M*(i%M-1)/2)%M*getmu(n/i)%M;
		i=j+1;
	} return mu2[n]=r%M;
}
int main() {
    fill(isp,isp+MAX+1,1);
    mu[1]=1;
    for(ll i=2;i<=MAX;i++) {
        if(isp[i]) {p.push_back(i);mu[i]=-1;}
        for(ll j:p) {
            if(i*j>MAX) break;
            isp[i*j]=0;
            if(i%j==0) {mu[i*j]=0;break;}
            mu[i*j]=mu[i]*mu[j];
        }
    } for(ll i=2;i<=MAX;i++) mu[i]=(mu[i-1]+mu[i]*i)%M;
    ll n,r=0;
    cin>>n;
	ll i=n;
	ll h1=getmu(n),h2;
	while(i) {
		ll j=n/i;
		ll ii=n/(j+1);
		h2=getmu(ii);
        ll x=j%M;
		r+=(h1-h2)*x%M*x%M*(x+1)%M;
		r%=M;
		i=ii;
		h1=h2;
	} if(r<0) r+=M;
	cout<<r;
}
