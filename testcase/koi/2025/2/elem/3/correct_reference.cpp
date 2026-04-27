#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll inf=1e18;
ll n,m,i,j,k,l,r,x,y,z,w,s,t,dp[1100][1100],par[1100000],h[1100000],ans[1100000];
pair<ll,ll> p[1100000];
queue<ll> q;
vector<ll> v[1100000];
ll f(ll x)
{
    if(par[x]==x)
        return x;
    par[x]=f(par[x]);
    return par[x];
}
void g(ll x,ll y)
{
    x=f(x);
    y=f(y);
    if(x==y)
        return;
    if(h[y]<h[x])
        swap(x,y);
    h[y]+=h[x];
    par[x]=y;
}
int main()
{
    scanf("%lld %lld",&n,&m);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
    {
        dp[i][j]=inf;
    }
    for(i=1;i<=n;i++)
    {
        dp[i][i]=0;
    }
 
    for(i=1;i<=m;i++)
    {
        scanf("%lld %lld",&x,&y);
        p[i]={x,y};
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(i=1;i<=n;i++)
    {
        dp[i][i]=0;
        q.push(i);
        while(!q.empty())
        {
            x=q.front();
            q.pop();
            for(auto xx:v[x])
            {
                if(dp[i][xx]>dp[i][x]+1)
                {
                    dp[i][xx]=dp[i][x]+1;
                    q.push(xx);
                }
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        h[i]=1;
        par[i]=i;
    }
    s=0;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        s+=dp[i][j];
    for(i=m;i>=1;i--)
    {
        ans[i]=s;
        x=p[i].first;
        y=p[i].second;
        x=f(x);
        y=f(y);
        if(x==y)
        {
            continue;
        }
        for(j=1;j<=n;j++)
        {
            for(k=1;k<=n;k++)
            {
                dp[j][k]=min(dp[j][k],dp[j][x]+dp[y][k]);
                dp[j][k]=min(dp[j][k],dp[j][y]+dp[x][k]);
            }
        }
        s=0;
        for(j=1;j<=n;j++)
            for(k=1;k<=n;k++)
            s+=dp[j][k];
        g(x,y);
    }
    for(i=1;i<=m;i++)
    {
        printf("%lld\n",ans[i]);
    }
}
