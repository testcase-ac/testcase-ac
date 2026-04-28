#include <stdio.h>
#include <vector>
#define M 1000000007LL;
using namespace std;
typedef long long ll;
ll go[1000001];
//1<=a<b<=n에 대해서, gcd(a,b) = 1인 pair쌍의 ab 값의 합.
ll dp[1000001];
vector <ll> v;
vector <ll> bit[128];
void init();
void bunhae(ll x);
ll calc(ll x);
int main(void)
{
    ll n,ans=0; init(); scanf("%lld",&n);
    for(ll i=2;i<=n;i++)
    {
        bunhae(i);
        dp[i] = dp[i-1] + calc(i); dp[i]%=M;
        //printf("dp[%lld] = %lld\n",i,dp[i]);
    }
    for(ll gcd=1;gcd<=n;gcd++)
    {
        ans = ans + gcd*dp[n/gcd]; ans = ans%M;
    }
    printf("%lld\n",ans);
}
ll calc(ll x)
{
    //a = x, 1<=b<=x
    ll tot = (x*(x+1))/2;
    ll sz = (ll)v.size();
    for(ll i=1;i<(1<<sz);i++)
    {
        ll rr = 1, cou = (ll)bit[i].size();
        for(ll j=0;j<cou;j++)
            rr = rr * v[bit[i][j]];
        ll u = x/rr;
        ll T = rr*((u*(u+1))/2);
        if(cou%2)
            tot = tot - T;
        else
            tot = tot + T;
    }
    return tot*x;
}
void init()
{
    for(ll i=2;i<=1000000;i++)
    {
        if(go[i])
            continue;
        for(ll j=i;j<=1000000;j=j+i)
            go[j] = i;
    }
    for(ll i=1;i<128;i++)
    {
        for(ll j=0;j<7;j++)
        {
            if(i&(1<<j))
                bit[i].push_back(j);
        }
    }
}
void bunhae(ll x)
{
    ll cur = x;
    v.clear();
    while(cur!=1)
    {
        if(v.size() == 0 || v[v.size()-1]!=go[cur])
            v.push_back(go[cur]); 
        cur = cur/go[cur];
    }
}
