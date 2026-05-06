#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
int phi[200001];
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
int main() {
    for(int i=1;i<200001;i++) phi[i]=i;
    for(int i=2;i<200001;i++) {
        if(phi[i]==i) for(int j=i;j<200001;j+=i) phi[j]-=phi[j]/i;
    } int t,k;
    cin>>t;
    while(t--) {
        cin>>k;
        ll a[k],b[k],r=0,x=1,m=1e9;
        for(int i=0;i<k;i++) {cin>>a[i]>>b[i];m=min(m,b[i]);x=x*(b[i]-a[i]+1)%M;}
        for(int i=1;i<=m;i++) {
            ll t=phi[i];
            for(int j=0;j<k;j++) t=t*(b[j]/i-(a[j]-1)/i)%M;
            r+=t;
        } cout<<(M-r%M)*pw(x,M-2)%M<<'\n';
    }
}
