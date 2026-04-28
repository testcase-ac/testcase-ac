#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int mod = 1e9;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int size[101010];
int  chk[101010];
int n;
map<p, int> mp;
set<int> g[101010];

void dfs(int now, int prv, ll &dist){
	for(auto nxt : g[now]){
		if(nxt ^ prv && !chk[nxt]){
			chk[nxt] = 1;
			dfs(nxt, now, dist);
			size[now] += size[nxt];
		}
	}
	ll tmp = (ll)size[now] * (ll)(n - size[now]);
	tmp %= mod;
	dist += tmp; dist %= mod;
}

ll getDist(){
	ll ret = 0;
	chk[1] = 1;
	dfs(1, 0, ret);
	return ret;
}

void makeTree(vector<p> &v){
	sort(v.begin()+1, v.end());
	memset(size, 0, sizeof size);
	memset(chk, 0, sizeof chk);
	for(int i=0; i<=n; i++) g[i].clear();
	mp.clear();

	int cnt = 1;
	mp[v[1]] = cnt;
	size[cnt]++;
	for(int i=2; i<=n; i++){
		if(v[i-1].x == v[i].x && v[i-1].y+1 == v[i].y){
			mp[v[i]] = cnt;
		}
		else mp[v[i]] = ++cnt;
		size[cnt]++;
	}

	for(int i=1; i<=n; i++){
		int x = v[i].x, y = v[i].y;
		int now = mp[v[i]];
		for(int k=0; k<4; k++){
			int xx = x + dx[k];
			int yy = y + dy[k];
			int nxt = mp[{xx, yy}];
			if(nxt && now != nxt) g[now].insert(nxt);
		}
	}
}

int DistanceSum(int N, int *X, int *Y){
	n = N;
	ll ret = 0;
	vector<p> v(n+1);
	for(int i=0; i<n; i++){
		v[i+1] = {X[i], Y[i]};
	}
	makeTree(v);
	ret += getDist() % mod;

	for(int i=0; i<n; i++){
		v[i+1] = {Y[i], X[i]};
	}
	makeTree(v);
	ret += getDist() % mod;
	ret %= mod;
	return (int)ret;
}
