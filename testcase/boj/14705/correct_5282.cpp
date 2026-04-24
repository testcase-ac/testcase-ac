#include <bits/stdc++.h>
using namespace std;

bool seen[2][500000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, a, b, da, db, t = 0;
	cin >> n >> a >> b >> da >> db;
	queue<int> que;
	que.push(abs(a-b));
	seen[1][abs(a-b)] = true;
	while(!que.empty()) {
		int d = (t%2 == 0 ? da : db);
		int s = (int)que.size();
		while(s--) {
			int q = que.front();
			if(!q) return !(cout << t);
			que.pop();
			int nq = (q+d)%n;
			if(!seen[t&1][nq]) {
				seen[t&1][nq] = true;
				que.push(nq);
			}
			nq = (q+(n-d))%n;
			if(!seen[t&1][nq]) {
				seen[t&1][nq] = true;
				que.push(nq);
			}
		}
		t++;
	}
	cout << "Evil Galazy";
}
