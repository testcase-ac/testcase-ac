#include <bits/stdc++.h>
#define ll long long
using namespace std;
const double pisq=9.8696044010893586188344909998761511;
const ll MAX=5e7;
bool isp[MAX];
vector<int> p;
vector<ll> mu(MAX+1,0);
unordered_map<ll,ll> mu2;
ll getmu(ll n) {
    if(n<=MAX) return mu[n];
    unordered_map<ll,ll>::iterator x=mu2.find(n);
    if(x!=mu2.end()) return x->second;
    ll r=1,j;
    for(ll i=2;i<=n;) {
        j=n/(n/i);
        r-=(j-i+1)*getmu(n/i);
        i=j+1;
    } return mu2[n]=r;
}
ll sqfree(ll n) {
	ll r=n,j,m=1,t;
	for(ll i=2;i*i<=n;i=j+1) {
	    j=sqrt(n/(n/(i*i)));
	    t=getmu(j);
	    r+=(n/(i*i))*(t-m);
	    m=t;
	} return r;
}
int main() {
    fill(isp,isp+MAX,1);
    mu[1]=1;
    int i;
    for(i=2;i<=MAX;i++){
        if(isp[i]) {p.push_back(i);mu[i]=-1;}
        for(int& j:p){
            if(i*j>=MAX)break;
            isp[i*j]=0;
            if(i%j==0) {mu[i*j]=0;break;}
            mu[i*j]=mu[i]*mu[j];
        }
    } for(int i=2;i<=MAX;i++) mu[i]+=mu[i-1];
	ll n;
	cin>>n;
	ll p=(ll)((double)n/6.0*pisq);
	ll l=max(0LL,p-50000),r=min((ll)4e18,p+50000);
	while(l<r-1) {
		ll m=(l+r)/2;
		if(sqfree(m)<n) l=m;
		else r=m;
	} cout<<r;
}
