#include<iostream>
#include<vector>
#include<algorithm>
#define ep emplace
#define eb emplace_back
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
using namespace std;
typedef long long ll;
typedef pair<int,int>pi;
typedef pair<ll,ll>pl;
const int inf=1e9+7;
const ll INF=1e18;
struct unit
{
    vector<ll>x,y;
    ll z,w;
};
unit pre[64],solo[64];
int k;
inline unit merge(unit x,unit y)
{
    unit z;
    z.x=x.x;
    z.y=y.y;
    z.z=max(x.z,y.z);
    z.w=x.w+y.w;
    if(x.w<=k)
    {
        z.x.pop_back();
        for(int i=0;i<(int)y.x.size()&&(int)z.x.size()<=k;i++)
            z.x.eb(x.z+y.x[i]);
    }
    if(y.w<=k)
    {
        z.y.pop_back();
        for(int i=0;i<(int)x.y.size()&&(int)z.y.size()<=k;i++)
            z.y.eb(y.z+x.y[i]);
    }
    int mx=min((ll)k,z.w);
    for(int i=mx+1-(int)y.x.size();i<(int)x.y.size();i++)
        z.z=max(z.z,x.y[i]+y.x[mx-i]);
    return z;
}
int lev;
inline void precal()
{
    pre[0]=solo[0];
    for(int i=0;i++<lev;)
        pre[i]=merge(merge(pre[i-1],solo[i]),pre[i-1]);
    return;
}
int num_trailing_zeros(ll x) {
    int c = 0;
    while (x > 0 && x % 2 == 0) x /= 2, c++;
    return c;
}
int num_leading_zeros(ll x) {
    int c = 0;
    while (x > 0 && (x & (1ll << 63)) == 0) x <<= 1, c++;
    return c;
}

ll i,j;
unit dnc(ll s,ll e)
{
    ll m=s+(e-s)/2;
    int cl=num_trailing_zeros(m);
    if(i<=s&&e<=j)
        return pre[cl];
    if(j<m)
        return dnc(s,m-1);
    if(i>m)
        return dnc(m+1,e);
    if(i==m)
    {
        unit r=dnc(m+1,e);
        return merge(solo[cl],r);
    }
    unit l=dnc(s,m-1);
    if(j==m)
        return merge(l,solo[cl]);
    unit r=dnc(m+1,e);
    return merge(merge(l,solo[cl]),r);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    int tcn;
    cin>>n>>tcn;
    lev=63-num_leading_zeros(n);
    for(int tci=0;tci++<tcn;)
    {
        cin>>i>>j>>k;
        for(int i=0;i<=lev;i++)
        {
            int cur=n>>(lev-i)&1;
            solo[i].x=vector<ll>(1,cur);
            solo[i].y=vector<ll>(1,cur);
            if(k>0&&cur==0)
                solo[i].x.eb(1),solo[i].y.eb(1);
            solo[i].z=k==0?cur:1;
            solo[i].w=1-cur;
        }
        precal();
        unit v;
        if(i==j)
            v=solo[num_trailing_zeros(i)];
        else
            v=dnc(1,(1ll<<(lev+1))-1);
        cout<<v.z<<'\n';
    }
    return 0;
}