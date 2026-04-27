#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
using namespace std;
using ll=long long;
using pll=array<ll,2>;
using tll=array<ll,3>;
using tl5=array<ll,5>;
const int N=300005;
int n,a[N];
ll score[N],cnt[N];
vector<pll> g[N];
int rt,vis[N],sz[N],sub[N],grp[N],grpsz[N];
pll subF[N],ttlF;
ll csub[N],cttl;
tll stk[N]; int stksz;
tl5 ev[N]; int evsz;
pll qry[N]; int qrysz;
void calcSize(int u,int p){
	sz[u]=1;
	for(auto [v,w]: g[u]) if(p!=v&&!vis[v]){
		calcSize(v,u);
		sz[u]+=sz[v];
	}
}
int findCentroid(int u,int p,int S){
	for(auto [v,w]: g[u]) if(p!=v&&!vis[v]&&sz[v]>=S) return findCentroid(v,u,S);
	return u;
}
void dfsSub(int u,int p,ll val,ll sum){
	grpsz[grp[u]]++;
	if(grp[u]==rt){
		subF[sub[u]][0]++;
		ttlF[0]++;
	}
	subF[sub[u]][1]+=val;
	ttlF[1]+=val;
	for(auto [v,w]: g[u]) if(p!=v&&!vis[v]){
		sub[v]=sub[u];
		if(val+w>=0) grp[v]=grp[u];
		else{
			grp[v]=v;
			grpsz[v]=0;
		}
		dfsSub(v,u,max(0ll,val+w),sum+w);
		if(val+w<0){
			csub[sub[v]]+=sz[v];
			cttl+=sz[v];
			ev[++evsz]={-sum-w,sub[v],grpsz[v],(sum+w)*grpsz[v],sz[v]};
		}
	}
}
void dfsPath(int u,int p,ll sum){
	int osz=stksz;
	tll oval;
	if(!stksz||stk[1][0]<=sum){
		stksz=1;
		oval=stk[stksz];
		stk[stksz]={sum,sum,0};
		qry[++qrysz]={sum,u};
	} else{
		int l=2,r=stksz;
		while(l<=r){
			int m=(l+r)>>1;
			if(sum<stk[m][0]) l=m+1;
			else r=m-1;
		}
		stksz=l;
		oval=stk[stksz];
		stk[stksz]={sum,stk[l-1][1],stk[l-1][2]+1};
		cnt[u]+=(stk[l-1][2]+1)*(sz[rt]-sz[sub[u]]);
		qry[++qrysz]={stk[l-1][1],u};
	}
	for(auto [v,w]: g[u]) if(p!=v&&!vis[v]) dfsPath(v,u,sum+w);
	stk[stksz]=oval;
	stksz=osz;
}
void solve(int r){
	calcSize(r,0);
	r=findCentroid(r,0,(sz[r]+1)/2);
	calcSize(r,0);
	rt=r;
	ttlF={1,0};
	cttl=0;
	evsz=0;
	grpsz[r]=0;
	for(auto [u,w]: g[r]) if(!vis[u]){
		subF[u]={0,0};
		csub[u]=0;
		sub[u]=u;
		if(w>=0) grp[u]=r;
		else{
			grp[u]=u;
			grpsz[u]=0;
		}
		dfsSub(u,r,max(0ll,w),w);
		if(w<0){
			csub[u]+=sz[u];
			cttl+=sz[u];
			ev[++evsz]={-w,u,grpsz[u],w*grpsz[u],sz[u]};
		}
	}
	qrysz=0;
	stksz=0;
	dfsPath(r,0,0);
	sort(ev+1,ev+1+evsz);
	sort(qry+1,qry+1+qrysz);
	for(int i=1,j=1;i<=qrysz;i++){
		while(j<=evsz&&ev[j][0]<=qry[i][0]){
			subF[ev[j][1]][0]+=ev[j][2];
			subF[ev[j][1]][1]+=ev[j][3];
			ttlF[0]+=ev[j][2];
			ttlF[1]+=ev[j][3];
			csub[ev[j][1]]-=ev[j][4];
			cttl-=ev[j][4];
			j++;
		}
		int u=qry[i][1];
		ll x=qry[i][0];
		score[u]+=ttlF[0]*x+ttlF[1];
		cnt[u]+=cttl;
		if(u!=r){
			score[u]-=subF[sub[u]][0]*x+subF[sub[u]][1];
			cnt[u]-=csub[sub[u]];
		}
	}
	vis[r]=1;
	for(auto [u,w]: g[r]) if(!vis[u]) solve(u);
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n;
	for(int u,v,w,i=1;i<n;i++){
		cin>>u>>v>>w;
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	solve(1);
	cout<<"1\n";
	for(int i=1;i<=n;i++) cout<<score[i]<<" \n"[i==n];
	for(int i=1;i<=n;i++) cout<<cnt[i]<<" \n"[i==n];
	return 0;
}