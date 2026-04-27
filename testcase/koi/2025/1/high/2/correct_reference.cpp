#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll inf=1e18;
ll n,m,i,j,k,l,r,x,y,z,w,s,t,a[1100000],b[1100000],dp[2200][2200],dp2[1100000],c[2200][2200],st,ed,ans;
vector<pair<ll,ll>> v[1100000];
vector<ll> u[1100000];
priority_queue<pair<ll,ll>> q;
queue<ll> qq;
int main()
{
    scanf("%lld %lld",&n,&m);
    for(i=1;i<=m;i++)
    {
        scanf("%lld %lld %lld",&x,&y,&z);
        v[x].push_back({y,z});
    }
    for(i=1;i<=n;i++)
    {
        q.push({0,i});
        for(j=1;j<=n;j++)
            dp[i][j]=inf;
        dp[i][i]=0;
        while(!q.empty())
        {
            x=q.top().second;
            q.pop();
            if(c[i][x])
                continue;
            c[i][x]=1;
            for(auto xx:v[x])
            {
                y=xx.first;
                z=xx.second;
                if(dp[i][y]>dp[i][x]+z)
                {
                    dp[i][y]=dp[i][x]+z;
                    q.push({-dp[i][y],y});
                }
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        scanf("%lld",&b[i]);
    }
    scanf("%lld %lld",&s,&t);
    st=1;
    ed=n;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(dp[i][j]<=s&&(b[j]==0||j==ed))
            {
                u[i].push_back(j);}
        }
    }
    for(i=1;i<=n;i++)
        dp2[i]=inf;
    dp2[st]=0;
    qq.push(st);
    while(!qq.empty())
    {
        x=qq.front();
        qq.pop();
        for(auto xx:u[x])
        {
            if(dp2[xx]>dp2[x]+1)
            {
                dp2[xx]=dp2[x]+1;
                qq.push(xx);
            }
        }
    }
    if(dp2[ed]==inf)
    {
        printf("-1");
        return 0;
    }
    ans=inf;
    for(i=1;i<=n;i++)
    {
        if(dp2[i]==inf)
            continue;
        if(dp[i][ed]<=s)
        {
            ans=min(ans,dp2[i]*(s+t)+dp[i][ed]);
        }
    }
    printf("%lld",ans);
}
