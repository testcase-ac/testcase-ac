#include <bits/stdc++.h>
using namespace std;

int dist[2001][2001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	queue<pair<int, int>> que({{1,0}});
	memset(dist, 0x3f, sizeof dist);
	int t = 0;
	dist[1][0] = 0;
	auto visit = [&](int a, int b) {
		if(0 <= a && a <= 2000 && t+1 < dist[a][b]) {
			dist[a][b] = t+1;
			que.push({a,b});
		}
	};
	while(!que.empty()) {
		int s = que.size();
		while(s--) {
			int e, c;
			tie(e,c) = que.front();
			que.pop();
			visit(e+c, c);
			visit(e, e);
			visit(e-1, c);
		}
		t++;
	}
	int n;
	cin >> n;
	cout << *min_element(dist[n], dist[n]+2001);
}
