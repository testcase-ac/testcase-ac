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
const int mxn=5e5;
inline vector<int>saf(const string&s)
{
    int n=s.size();
    vector<int>sa(n);
    for(int i=0;i<n;i++)
        sa[i]=i;
    vector<int>v(n,0);
    vector<int>cnt(n+1,0);
    for(int i=1;i<n*2;i*=2)
    {
        vector<int>v2(n);
        int mx=0;
        for(int j=0;j<n;j++)
        {
            if(i==1)
                v2[j]=s[j]=='('?0:1;
            else
                v2[j]=j+i/2<n?1+v[j+i/2]:0;
            cnt[v2[j]]++;
            mx=max(mx,v2[j]);
        }
        vector<int>sac(n);
        for(int j=0;j<mx;j++)
            cnt[j+1]+=cnt[j];
        for(int j=n;j-->0;)
            sac[--cnt[v2[j]]]=j;
        for(int j=0;j<=mx;j++)
            cnt[j]=0;
        vector<int>v1=v;
        mx=0;
        for(int j=0;j<n;j++)
            cnt[v1[j]]++,mx=max(mx,v1[j]);
        for(int j=0;j<mx;j++)
            cnt[j+1]+=cnt[j];
        for(int j=n;j-->0;)
            sa[--cnt[v1[sac[j]]]]=sac[j];
        for(int j=0;j<=mx;j++)
            cnt[j]=0;
        v[0]=0;
        for(int j=1;j<n;j++)
            v[sa[j]]=v[sa[j-1]]+(v1[sa[j-1]]==v1[sa[j]]&&v2[sa[j-1]]==v2[sa[j]]?0:1);
    }
    return sa;
}
inline vector<int>lcpf(const string&s,const vector<int>&sa)
{
    int n=s.size();
    vector<int>ord(n);
    for(int i=0;i<n;i++)
        ord[sa[i]]=i;
    vector<int>lcp(n);
    for(int i=0;i<n;i++)
    {
        int&r=lcp[ord[i]];
        r=i>0?max(lcp[ord[i-1]]-1,0):0;
        if(ord[i]==0)
            r=0;
        else
        {
            int j=sa[ord[i]-1];
            while(i+r<n&&j+r<n&&s[i+r]==s[j+r])
                r++;
        }
    }
    return lcp;
}
inline vector<int>lcsf(string s,string t,const vector<int>&sa,const vector<int>&lcp)
{
    int n=s.size(),m=t.size();
    vector<int>lcs(n,0);
    for(int i=1,mx=sa[0]<n?0:n+m-sa[0];i<n+m;i++)
    {
        mx=min(mx,lcp[i]);
        if(sa[i]<n)
            lcs[sa[i]]=max(lcs[sa[i]],mx);
        else
            mx=n+m-sa[i];
    }
    for(int i=n+m,mx=sa[n+m-1]<n?0:n+m-sa[n+m-1];i-->1;)
    {
        mx=min(mx,lcp[i]);
        if(sa[i-1]<n)
            lcs[sa[i-1]]=max(lcs[sa[i-1]],mx);
        else
            mx=n+m-sa[i-1];
    }
    return lcs;
}
vector<int>vv[mxn+10];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tcn;
    cin>>tcn;
    for(int tci=0;tci++<tcn;)
    {
        string s,t;
        ll kv;
        cin>>s>>t>>kv;
        int n=s.size(),m=t.size();
        if(n>m)
            swap(n,m),swap(s,t);
        string d=s+t;
        vector<int>sa=saf(d);
        vector<int>lcp=lcpf(d,sa);
        vector<int>lcs=lcsf(s,t,sa,lcp);
        for(int i=0;i<n;i++)
            lcs[i]=min(lcs[i],n-i);
        vector<int>high(n+1,0);
        for(int i=0;i<n;i++)
            high[i+1]=high[i]+(s[i]=='('?1:-1);
        int hmin=inf;
        for(int&t:high)
            hmin=min(hmin,t);
        hmin--;
        for(int&t:high)
            t-=hmin;
        for(int i=0;i<=n;i++)
            vv[high[i]].eb(i);
        int mnp=0;
        for(int ii=0;ii<n+m;ii++)
        {
            int i=sa[ii];
            mnp=min(mnp,lcp[ii]);
            if(i>=n)
                continue;
            if(s[i]==')')
                break;
            int ch=high[i];
            auto it1=lower_bound(all(vv[ch-1]),i);
            int mxp=i+lcs[i];
            if(it1!=vv[ch-1].end())
                mxp=min(mxp,*it1);
            if(mnp+i<mxp)
            {
                auto it2=upper_bound(all(vv[ch]),mnp+i);
                auto it3=upper_bound(all(vv[ch]),mxp);
                if(kv<=it3-it2)
                {
                    int ls=*(it2+(kv-1));
                    for(int j=i;j<ls;j++)
                        cout<<s[j];
                    kv=0;
                    break;
                }
                else
                    kv-=it3-it2;
                mnp=mxp-i;
            }
        }
        if(kv>0)
            cout<<-1;
        cout<<'\n';
        for(int i=0;i<n+2;i++)
            vv[i].clear();
    }
    return 0;
}