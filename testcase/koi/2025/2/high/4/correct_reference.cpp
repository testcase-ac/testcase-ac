#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=300005;
const ll inf=1e18;
int n,k,p[N];
ll w[N],sum[N],ans[N];
ll cdp[2][N],ndp[N];
multiset<ll> dp[N];
vector<int> c[N];
void mrg(int u,int v){
	if(dp[u].size()<dp[v].size()){
		swap(dp[u],dp[v]);
		swap(sum[u],sum[v]);
	}
	if(dp[v].empty()) return;
	int h=dp[v].size(),h2=dp[u].size();
	if(h+2<=min(h2,k-h)){
		for(int i=1;i<=h;i++){
			auto iter=prev(dp[u].end());
			cdp[0][i]=cdp[0][i-1]+*iter;
			dp[u].erase(iter);
		}
		for(int i=1;i<=h;i++){
			auto iter=prev(dp[v].end());
			cdp[1][i]=cdp[1][i-1]+*iter;
			dp[v].erase(iter);
		}
		for(int i=h2;i>=k-h+1;i--){
			auto iter=dp[u].begin();
			cdp[0][i]=sum[u];
			sum[u]-=*iter;
			dp[u].erase(iter);
		}
		ndp[min(h2,k-h)]=sum[u]+sum[v];
		auto iter=prev(dp[u].end());
		ndp[h+1]=cdp[0][h]+*iter+sum[v];
		dp[u].erase(iter);
		for(int i=1;i<=h;i++) ndp[i]=cdp[0][i]+cdp[1][i];
		for(int i=k-h+1;i<=h2;i++) ndp[i]=cdp[0][i]+cdp[1][k-i];
		for(int i=1;i<=h+1;i++) ndp[i]=max(ndp[i],ndp[i-1]);
		for(int i=k-h+1;i<=h2;i++) ndp[i]=max(ndp[i],ndp[i-1]);
		for(int i=1;i<=h+1;i++) dp[u].insert(ndp[i]-ndp[i-1]);
		for(int i=k-h+1;i<=h2;i++) dp[u].insert(ndp[i]-ndp[i-1]);
		sum[u]=ndp[h2];
	} else{
		h=dp[u].size();
		for(int i=1;i<=h;i++){
			auto iter=prev(dp[u].end());
			cdp[0][i]=cdp[0][i-1]+*iter;
			dp[u].erase(iter);
		}
		for(int i=1;i<=h;i++){
			if(dp[v].empty()){
				cdp[1][i]=cdp[1][i-1];
				continue;
			}
			auto iter=prev(dp[v].end());
			cdp[1][i]=cdp[1][i-1]+*iter;
			dp[v].erase(iter);
		}
		for(int i=1;i<=h;i++) ndp[i]=max(cdp[0][i]+cdp[1][min(i,k-i)],cdp[1][i]+cdp[0][min(i,k-i)]);
		for(int i=1;i<=h;i++) ndp[i]=max(ndp[i],ndp[i-1]);
		sum[u]=ndp[h];
		for(int i=1;i<=h;i++) dp[u].insert(ndp[i]-ndp[i-1]);
	}
	while(dp[u].size()&&!*dp[u].begin()) dp[u].erase(dp[u].begin());
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>k;
	for(int i=2;i<=n;i++){
		cin>>p[i]>>w[i];
		c[p[i]].push_back(i);
	}
	for(int u=n;u>=1;u--){
		for(int v: c[u]) mrg(u,v);
		ans[u]=sum[u];
		if(w[u]){
			dp[u].insert(w[u]);
			sum[u]+=w[u];
			if((int)dp[u].size()>k){
				sum[u]-=*dp[u].begin();
				dp[u].erase(dp[u].begin());
			}
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<"\n";
	return 0;
}