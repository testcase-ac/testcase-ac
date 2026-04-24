#include <bits/stdc++.h>
using namespace std;
#define rep(i, N) for(int i=0; i<N; i++)
int arr[10][10], num[10][10], dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1}, R, C, par[10];
void dfs(int r, int c) {
	for(int t=0; t<4; t++) {
		int tr = r + dr[t], tc = c + dc[t];
		if(0 <= tr && tr < R && 0 <= tc && tc < C && arr[r][c] && !num[tr][tc] && arr[tr][tc]) {
			num[tr][tc] = num[r][c];
			dfs(tr, tc);
		}
	}
}
int f(int i) {return par[i] == i ? i : par[i] = f(par[i]);}
int main() {
	cin >> R >> C;
	rep(r, R) rep(c, C) cin >> arr[r][c];
	int k = 1;
	rep(r, R) rep(c, C)
		if(arr[r][c] && !num[r][c]) {
			par[k] = k;
			num[r][c] = k++;
			dfs(r, c);
		}
	for(int i=1; i<k; i++) par[i] = i;
	vector<tuple<int,int,int>> edges;
	rep(r, R)
		for(int c1=0, c2=0; c1<C; c1=c2) {
			while(c2 < C && arr[r][c1] == arr[r][c2])
				c2++;
			if(c1 - 1 >= 0 && c2 < C && c2 - c1 > 1 && num[r][c1-1] && num[r][c2])
				edges.push_back({c2-c1, num[r][c1-1], num[r][c2]});
		}
	rep(c, C)
		for(int r1=0, r2=0; r1<R; r1=r2) {
			while(r2 < R && arr[r1][c] == arr[r2][c])
				r2++;
			if(r1 - 1 >= 0 && r2 < R && r2 - r1 > 1 && num[r1-1][c] && num[r2][c])
				edges.push_back({r2 - r1, num[r1-1][c], num[r2][c]});
		}
	sort(edges.begin(), edges.end());
	int ans = 0, cnt = 0;
	for(auto [w, u, v]: edges)
		if(f(u) != f(v)) {
			par[f(u)] = f(v);
			ans += w;
			cnt++;
		}
	cout << ((cnt != k - 2) ? -1 : ans);
}
