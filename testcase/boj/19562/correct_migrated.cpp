#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=998244353;
using mat=vector<vector<ll>>;
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
void hessenberg(mat&A) {
    int n=A.size();
    for(int i=1;i<n;i++) {
        for(int j=i;j<n;j++) { 
            if(A[j][i-1]!=0) {
                swap(A[i],A[j]);
                for(int k=0;k<n;k++) swap(A[k][i],A[k][j]);
                break;
            }
        } if(A[i][i-1]==0) continue;
        ll x=A[i][i-1],y=pw(x,M-2);
        for(int j=0;j<n;j++) A[j][i]=A[j][i]*x%M;
        for(int j=i-1;j<n;j++) A[i][j]=A[i][j]*y%M;
        for(int j=i+1;j<n;j++) {
            ll z=A[j][i-1]%M,w=(M-z)%M;
            for(int k=0;k<n;k++) A[k][i]=(A[k][j]*z+A[k][i])%M;
            for(int k=i-1;k<n;k++) A[j][k]=(A[i][k]*w+A[j][k])%M;
        }
    }
}
vector<ll> charpoly(mat A) {
    hessenberg(A);
    int n=A.size();
    vector<vector<ll>> dp(n+1,vector<ll>(n+1));
    dp[0][0]=1;
    for(int i=0;i<n;i++) {
        ll x=1;
        for(int j=i;j>=0;j--) {
            ll y=(M-x*A[j][i]%M)%M;
            for(int k=0;k<=j;k++) dp[i+1][k]=(y*dp[j][k]+dp[i+1][k])%M;
            if(j) x=x*A[j][j-1]%M;
        } for(int k=0;k<=i;k++) dp[i+1][k+1]=(dp[i][k]+dp[i+1][k+1])%M;
    } return dp[n];
}
ll eval(vector<ll> p,ll x) {
    ll r=0;
    for(int i=p.size()-1;i>=0;i--) r=(r*x+p[i])%M;
    return r;
}
int main() {
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    mat A(n,vector<ll>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) {
        ll x;
        cin>>x;
        A[i][j]=x;
    } auto p=charpoly(A);
    if(n%2) for(auto &i:p) i=(M-i)%M;
    while(q--) {
        ll x;
        cin>>x;
        cout<<eval(p,x)<<' ';
    }
}
