#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MX = 1e5+2;
int opt[201][MX];
ll dp[2][MX], acc[MX], arr[MX];
struct Line {
	ll a, b;
	int i;
	ll eval(ll x) {
		return a*x + b;
	}
};
struct CHT {
	// increasing slope, increasing query, max query
	deque<Line> dq;
	int lst_x;
	CHT() {
		lst_x = 0;
	}
	void add(Line c) {
		while(dq.size() >= 2) {
			Line a = dq[dq.size()-2], b = dq.back();
			if((b.b-c.b)*(b.a-a.a) <= (a.b-b.b)*(c.a-b.a)) {
				dq.pop_back();
			} else {
				break;
			}
		}
		dq.push_back(c);
	}
	ll query(ll x) {
		while(dq.size() >= 2 && dq[0].eval(x) <= dq[1].eval(x)) {
			dq.pop_front();
		}
		lst_x = x;
		return dq.front().eval(x);
	}
};
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
		acc[i] += acc[i-1] + arr[i];
	}
	for(int i=1; i<=k; i++) {
		int c = i&1, p = c^1;
		CHT cht;
		for(int j=1; j<=n; j++) {
			cht.add({acc[j-1], dp[p][j-1]-acc[j-1]*acc[j-1], j});
			dp[c][j] = cht.query(acc[j]);
			opt[i][j] = cht.dq.front().i;
		}
	}
	cout << dp[k&1][n] << '\n';
	vector<int> v;
	int a = k, b = n;
	while(a) {
		v.push_back(opt[a][b]-1);
		b = opt[a][b]-1;
		a--;
	}
	reverse(v.begin(), v.end());
	for(int t: v)
		cout << t << ' ';
}
