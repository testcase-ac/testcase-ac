#include <bits/stdc++.h>
using namespace std;
int n, arr[500][1000], prv[250001], di[] = {0,1,0,-1}, dj[] = {1,0,-1,0};
queue<pair<int, int>> que;
int conv(int i, int j) {
	return i/2*(2*n-1)+((i&1)?n:0)+(j-(i&1))/2;
}
void add(int i, int j, int p) {
	int c = conv(i, j);
	if(prv[c] != -1) return;
	int jc = i&1 ? ((j+1)^1)-1 : j^1;
	que.push({i, j});
	que.push({i, jc});
	prv[c] = p;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		for(int j=i&1; j<2*n-(i&1); j++) {
			cin >> arr[i][j];
		}
	}
	memset(prv, -1, sizeof prv);
	add(0, 0, 0);
	while(!que.empty()) {
		int i, j;
		tie(i, j) = que.front();
		que.pop();
		for(int t=0; t<4; t++) {
			int ti = i+di[t], tj = j+dj[t];
			if(0 <= ti && ti < n && 0 <= tj && tj < 2*n && arr[i][j] == arr[ti][tj])
				add(ti, tj, conv(i,j));
		}
	}
	int i = n*n;
	while(prv[i] == -1)
		i--;
	vector<int> ans;
	while(i) {
		ans.push_back(i);
		i = prv[i];
	}
	ans.push_back(0);
	reverse(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	for(int j: ans) cout << j+1 << ' ';
}
