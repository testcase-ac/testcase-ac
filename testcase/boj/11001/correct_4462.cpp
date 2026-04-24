#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+2;
int t[MX], v[MX];
struct line {
	int a, b, t;
	int eval(int x) {
		return a*x+b;
	}
};
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, d;
	cin >> n >> d;
	for(int i=0; i<n; i++) {
		cin >> t[i];
	}
	for(int i=0; i<n; i++) {
		cin >> v[i];
	}
	deque<line> dq;
	int ans = 0;
	for(int i=0; i<n+d; i++) {
		//printf("at i=%d\n", i);
		if(i < n) {
			line l = {-t[i], i*t[i], i};
			while(dq.size() && l.eval(max(0ll, i-d)) >= dq.back().eval(max(0ll, i-d))) {
				dq.pop_back();
			}
			dq.push_back(l);
		}
		if(i >= d) {
			int st = i-d;
			while(dq.front().t < st || (dq.size() >= 2 && dq[0].eval(st) <= dq[1].eval(st))) {
				//printf("popping line %dx+%d\n", dq.front().a, dq.front().b);
				dq.pop_front();
			}
			//printf("selected line is %dx+%d. evals to %d\n", dq.front().a, dq.front().b, dq.front().eval(st)+v[st]);
			ans = max(ans, dq.front().eval(st)+v[st]);
		}
	}
	cout << ans;
}
