#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1000000007;
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
ll f[200001];
ll com(ll n,ll k) {return (((f[n]*pw(f[k],M-2))%M)*pw(f[n-k],M-2))%M;}
ll det(vector<vector<ll>> a) {
    int n=a.size();
    ll r=1;
    for(int i=0;i<n;i++) {
        int p=i;
        while(p<n&&a[p][i]==0) p++;
        if(p==n) return 0;
        if(i!=p) swap(a[i],a[p]),r=M-r;
        r=r*a[i][i]%M;
        ll inv=pw(a[i][i],M-2);
        for(int j=i+1;j<n;j++) {
            ll f=a[j][i]*inv%M;
            for(int k=i;k<n;k++) a[j][k]=(a[j][k]-f*a[i][k])%M;
        }
    } return (r+M)%M;
}
int main() {
    f[0]=1;
    for(int i=1;i<=200000;i++) f[i]=f[i-1]*i%M;
    int t,n,k;
    cin>>t;
    while(t--) {
        cin>>n>>k;
        ll a[k],b[k];
        for(int i=0;i<k;i++) cin>>a[i];
        for(int i=0;i<k;i++) cin>>b[i];
        vector<vector<ll>> v(k,vector<ll>(k));
        for(int i=0;i<k;i++) {
            for(int j=0;j<k;j++) {
                if(b[j]<a[i]) v[i][j]=0;
                else v[i][j]=com(n-1+b[j]-a[i],n-1);
            }
        } cout<<det(v)<<'\n';
    }
}
