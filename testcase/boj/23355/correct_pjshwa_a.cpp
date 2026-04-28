#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 250005;

vector<int> gph[MAXN];
int dep[MAXN], par[18][MAXN], din[MAXN], dout[MAXN], piv;

bool in_subtree(int x, int y){
	return din[x] <= din[y] && dout[y] <= dout[x];
}

int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	int dx = dep[y] - dep[x];
	for(int i = 0; dx; i++){
		if(dx & 1) y = par[i][y];
		dx >>= 1;
	}
	for(int i = 17; i >= 0; i--){
		if(par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	}
	if(x != y) return par[0][x];
	return x;
}

void dfs(int x, int p){
	din[x] = piv++;
	for(auto &i : gph[x]){
		if(i != p){
			dep[i] = dep[x] + 1;
			par[0][i] = x;
			dfs(i, x);
		}
	}
	dout[x] = piv;
}

bool in_path(int x, int y, int z){
	return in_subtree(lca(x, y), z) && (in_subtree(z, x) || in_subtree(z, y));
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	for(int i = 1; i < 18; i++){
		for(int j = 1; j <= n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	int q; scanf("%d",&q);
	for(int i = 0; i < q; i++){
		int t, x, y;
		scanf("%d %d %d",&t,&x,&y);
		bool ans = 1;
		for(int j = 0; j < t; j++){
			int z; scanf("%d",&z);
			if(!in_path(x, y, z)) ans = 0;
		}
		puts(ans ? "NO" : "YES");
	}
}
