#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+1, MOD = 1e9;
int par[MX], sz[MX];
int f(int i){return par[i] == i ? i : par[i]=f(par[i]);}
pair<int, int> buk[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++) {
		par[i] = i;
		sz[i] = 1;
	}
	int tsum = 0, ans = 0, cur = 0;
	while(m--) {
		int x, y, w;
		cin >> x >> y >> w;
		buk[w] = {x, y};
		tsum += w;
	}
	for(int i=MX-1; i; i--) {
		if(!buk[i].first) continue;
		int x, y;
		tie(x, y) = buk[i];
		x = f(x), y = f(y);
		if(x != y) {
			ans += ((sz[x]*sz[y])%MOD*((tsum-cur)%MOD))%MOD;
			sz[y] += sz[x];
			par[x] = y;
		}
		cur += i;
	}
	cout << ans%MOD;
}
