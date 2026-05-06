#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=998244353;
int mu[1000001];
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
int main() {
    ll m,k,r=1;
    mu[1]=1;
    for(int i=1;i<1000001;i++) for(int j=i*2;j<1000001;j+=i) mu[j]-=mu[i];
    cin>>m>>k;
    for(ll i=1;i<=k;i++) r=(r+(pw(2*(k/i)+1,m)-1)*mu[i])%M;
    cout<<(r+M)%M;
}
