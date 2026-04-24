#include <bits/stdc++.h>
using namespace std;
char arr[50][51];
int val[50][50];
bool seen[50][50];
int di[] = {0,0,1,-1,1,1,-1,-1}, dj[] = {1,-1,0,0,1,-1,1,-1}, n, l, r;
int dfs(int i, int j) {
	int ret = arr[i][j] == 'K' || arr[i][j] == 'P';
	seen[i][j] = 1;
	for(int k=0; k<8; k++) {
		int ti = i+di[k], tj = j+dj[k];
		if(0 <= ti && ti < n && 0 <= tj && tj < n && !seen[ti][tj] && l <= val[ti][tj] && val[ti][tj] <= r)
			ret += dfs(ti, tj);
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int kcnt = 0, pi, pj;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
		for(int j=0; j<n; j++) {
			if(arr[i][j] == 'K')
				kcnt++;
			else if(arr[i][j] == 'P')
				pi = i, pj = j;
		}
	}
	set<int> st;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> val[i][j];
			st.insert(val[i][j]);
		}
	}
	vector<int> pval(st.begin(), st.end());
	int m = pval.size(), ans = INT_MAX;
	for(int i=0; i<m; i++) {
		int a = i, b = m;
		l = pval[i];
		if(l > val[pi][pj]) break;
		while(a < b) {
			int j = (a+b)/2;
			r = pval[j];
			memset(seen, 0, sizeof seen);
			if(val[pi][pj] > r || dfs(pi, pj) != kcnt+1)
				a = j+1;
			else
				b = j;
		}
		if(a < m)
			ans = min(ans, pval[a]-pval[i]);
	}
	cout << ans;
}
