#include <bits/stdc++.h>
using namespace std;
const int MX = 5e5+1;
int dist[MX][2];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	queue<int> que;
	que.push(n);
	memset(dist, -1, sizeof dist);
	dist[n][0] = 0;
	int t = 1;
	auto add = [&](int i) {
		if(i >= MX || i < 0 || dist[i][t&1] != -1) return;
		dist[i][t&1] = t;
		que.push(i);
	};
	while(que.size()) {
		int s = que.size();
		while(s--) {
			int q = que.front();
			que.pop();
			add(q*2);
			add(q+1);
			add(q-1);
		}
		t++;
	}
	t = 0;
	while(1) {
		int ct = k + t*(t+1)/2;
		if(ct >= MX) return !(cout << -1);
		if(dist[ct][t&1] != -1 && dist[ct][t&1] <= t)
			return !(cout << t);
		t++;
	}
}
