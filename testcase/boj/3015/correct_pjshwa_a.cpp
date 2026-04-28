#include "bits/stdc++.h"
#define pb push_back
#define fi first
#define se second
#define all(x) ((x).begin()), ((x).end())
#define compress(x) sort(all(x)), (x).erase(unique(all(x)),(x).end())
#define siz(x) ((int)((x).size()))
#define endl '\n'
using namespace std;
using ll = long long;
using pi = pair<int,int>;
using pl = pair<ll,ll>;
template<typename T>T rmin(T &a,T b){return a=min<T>(a,b);}
template<typename T>T rmax(T &a,T b){return a=max<T>(a,b);}

int N;
ll ans=0;
ll v[505050];

void dnc(int s,int e){
    if(s>=e)return;
    int m=(s+e)/2;
    vector<ll>a(1,v[m]),b(1,v[m]);
    for(int i=m-1;i>=s;i--)if(a.back()<=v[i])a.pb(v[i]);
    for(int i=m+1;i<=e;i++)if(b.back()<=v[i])b.pb(v[i]);
    for(ll i=m-1,mx=0;i>=s;i--){
        if(mx<=v[m] and mx<=v[i])ans++;
        rmax(mx,v[i]);
    }
    for(ll i=m+1,mx=0;i<=e;i++){
        if(mx<=v[m] and mx<=v[i])ans++;
        rmax(mx,v[i]);
    }
    for(int l=1,xr=0,r=0;l<siz(a);l++){
        while(r+1<siz(b) and b[r]<=a[l])r++;
        while(xr+1<siz(b) and b[xr+1]<a[l-1])xr++;
        ans+=(r-xr);
    }
    dnc(s,m-1);
    dnc(m+1,e);
}

int main(){
//    freopen("input.txt","r",stdin);
    ios::sync_with_stdio(0);cin.tie(0);
    
    cin>>N;
    for(int i=1;i<=N;i++)cin>>v[i];
    dnc(1,N);
    cout<<ans<<endl;
}
