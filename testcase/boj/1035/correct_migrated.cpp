#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	int cnt = 0;
	int vis[26][26][26][26][26]{};
	tuple<int, int, int, int, int> base = { 0,0,0,0,0 };
	for (int i = 1; i <= 25; i++) {
		char a;
		cin >> a;
		if (a == '*') {
			if (!get<0>(base)) {
				int &c = get<0>(base);
				c = i;
			}
			else if (!get<1>(base)) {
				int& c = get<1>(base);
				c = i;
			}
			else if (!get<2>(base)) {
				int& c = get<2>(base);
				c = i;
			}
			else if (!get<3>(base)) {
				int& c = get<3>(base);
				c = i;
			}
			else {
				int& c = get<4>(base);
				c = i;
			}
			cnt++;
		}
	}

	if (cnt == 1) { cout << 0; return 0; }

	auto chk = [&](int a, int b, int c, int d, int e) -> bool {
		
		int viss[26]{}, arrr[26]{};
		queue<int> QQ;
		viss[a]++;
		arrr[a] = arrr[b] = arrr[c] = arrr[d] = arrr[e] = 1;
		int cc = 0;
		QQ.push(a);
		while (!QQ.empty()) {
			int now = QQ.front();
			cc++;
			QQ.pop();
			if (now % 5 != 1) {
				if (arrr[now - 1] && !viss[now - 1])	QQ.emplace(now - 1), viss[now - 1]++;

			}
			if (now % 5) {
				if (arrr[now + 1] && !viss[now + 1])	QQ.emplace(now + 1), viss[now + 1]++;

			}
			if (now > 5) {
				if (arrr[now - 5] && !viss[now - 5])	QQ.emplace(now - 5), viss[now - 5]++;

			}
			if (a <= 20) {
				if (arrr[now + 5] && !viss[now + 5])	QQ.emplace(now + 5), viss[now + 5]++;

			}
		}
		return cc == cnt;
	};
	auto diff = [](int a, int b, int c, int d, int e) -> bool {
		bool res = 1;
		if (b)	res &= (a != b);
		if (c)	res &= (a != c && b != c);
		if (d)	res &= (a != d && b != d && c != d);
		if (e)	res &= (a != e && b != e && c != e && d != e);
		return res;
	};

	queue<tuple<int, int, int, int, int, int>> Q;
	auto [q, w, e, r, t] = base;
	vis[q][w][e][r][t]++;
	Q.emplace(q, w, e, r, t, 0);
	while (!Q.empty()) {
		auto [a, b, c, d, e, t] = Q.front();
		Q.pop();

		if (chk(a, b, c, d, e)) {
			cout << t;
			return 0;
		}
		if (a) {
			if (a % 5 != 1) {
				if (!vis[a - 1][b][c][d][e] && diff(a-1,b,c,d,e)) {
					Q.emplace(a - 1, b, c, d, e, t + 1);
					vis[a - 1][b][c][d][e]++;
				}
			}
			if (a % 5) {
				if (!vis[a + 1][b][c][d][e] && diff(a+1,b,c,d,e)) {
					Q.emplace(a + 1, b, c, d, e, t + 1);
					vis[a + 1][b][c][d][e]++;
				}
			}
			if (a > 5) {
				if (!vis[a - 5][b][c][d][e] && diff(a-5,b,c,d,e)) {
					Q.emplace(a - 5, b, c, d, e, t + 1);
					vis[a - 5][b][c][d][e]++;
				}
			}
			if (a <= 20) {
				if (!vis[a + 5][b][c][d][e] && diff(a+5,b,c,d,e)) {
					Q.emplace(a + 5, b, c, d, e, t + 1);
					vis[a + 5][b][c][d][e]++;
				}
			}
		}
		if (b) {
			if (b % 5 != 1) {
				if (!vis[a][b - 1][c][d][e] &&diff(a,b-1,c,d,e)) {
					Q.emplace(a, b - 1, c, d, e, t + 1);
					vis[a][b - 1][c][d][e]++;
				}
			}
			if (b % 5) {
				if (!vis[a][b + 1][c][d][e] && diff(a, b + 1, c, d, e)) {
					Q.emplace(a, b + 1, c, d, e, t + 1);
					vis[a][b + 1][c][d][e]++;
				}
			}
			if (b > 5) {
				if (!vis[a][b - 5][c][d][e] && diff(a, b - 5, c, d, e)) {
					Q.emplace(a, b - 5, c, d, e, t + 1);
					vis[a][b - 5][c][d][e]++;
				}
			}
			if (b <= 20) {
				if (!vis[a][b + 5][c][d][e] && diff(a, b+5, c, d, e)) {
					Q.emplace(a, b + 5, c, d, e, t + 1);
					vis[a][b + 5][c][d][e]++;
				}
			}
		}
		if (c) {
			if (c % 5 != 1) {
				if (!vis[a][b][c - 1][d][e] && diff(a, b, c-1, d, e)) {
					Q.emplace(a, b, c - 1, d, e, t + 1);
					vis[a][b][c - 1][d][e]++;
				}
			}
			if (c % 5) {
				if (!vis[a][b][c + 1][d][e] && diff(a, b, c +1, d, e)) {
					Q.emplace(a, b, c + 1, d, e, t + 1);
					vis[a][b][c + 1][d][e]++;
				}
			}
			if (c > 5) {
				if (!vis[a][b][c - 5][d][e] && diff(a, b, c - 5, d, e)) {
					Q.emplace(a, b, c - 5, d, e, t + 1);
					vis[a][b][c - 5][d][e]++;
				}
			}
			if (c <= 20) {
				if (!vis[a][b][c + 5][d][e] && diff(a, b, c +5, d, e)) {
					Q.emplace(a, b, c + 5, d, e, t + 1);
					vis[a][b][c + 5][d][e]++;
				}
			}
		}
		if (d) {
			if (d % 5 != 1) {
				if (!vis[a][b][c][d - 1][e] && diff(a, b, c, d-1, e)) {
					Q.emplace(a, b, c, d - 1, e, t + 1);
					vis[a][b][c][d - 1][e]++;
				}
			}
			if (d % 5) {
				if (!vis[a][b][c][d + 1][e] && diff(a, b, c, d +1, e)) {
					Q.emplace(a, b, c, d + 1, e, t + 1);
					vis[a][b][c][d + 1][e]++;
				}
			}
			if (d > 5) {
				if (!vis[a][b][c][d - 5][e] && diff(a, b, c, d - 5, e)) {
					Q.emplace(a, b, c, d - 5, e, t + 1);
					vis[a][b][c][d - 5][e]++;
				}
			}
			if (d <= 20) {
				if (!vis[a][b][c][d + 5][e] && diff(a, b, c, d+5, e)) {
					Q.emplace(a, b, c, d + 5, e, t + 1);
					vis[a][b][c][d + 5][e]++;
				}
			}
		}
		if (e) {
			if (e % 5 != 1) {
				if (!vis[a][b][c][d][e - 1] && diff(a, b, c, d , e-1)) {
					Q.emplace(a, b, c, d, e - 1, t + 1);
					vis[a][b][c][d][e - 1]++;
				}
			}
			if (e % 5) {
				if (!vis[a][b][c][d][e + 1] && diff(a, b, c, d, e +1)) {
					Q.emplace(a, b, c, d, e + 1, t + 1);
					vis[a][b][c][d][e + 1]++;
				}
			}
			if (e > 5) {
				if (!vis[a][b][c][d][e - 5] && diff(a, b, c, d, e - 5)) {
					Q.emplace(a, b, c, d, e - 5, t + 1);
					vis[a][b][c][d][e - 5]++;
				}
			}
			if (e <= 20) {
				if (!vis[a][b][c][d][e + 5] && diff(a, b, c, d, e + 5)) {
					Q.emplace(a, b, c, d, e + 5, t + 1);
					vis[a][b][c][d][e + 5]++;
				}
			}
		}
	}

}
