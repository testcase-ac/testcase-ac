#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Line {
	ll a, b;
	ll eval(ll x) {return a*x+b;}
	long double intersectX(Line l) {return (long double)(b-l.b)/(l.a-a);}
};
struct LineContainer {
	deque<Line> dq;
	void add(ll a, ll b) {
		Line cur = {a, b};
		while(dq.size() >= 2 && cur.intersectX(dq.back()) <= dq.back().intersectX(dq[dq.size()-2]))
			dq.pop_back();
		dq.push_back(cur);
	}
	ll query(ll x) {
		while(dq.size() >= 2 && dq[0].eval(x) <= dq[1].eval(x))
			dq.pop_front();
		return dq[0].eval(x);
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	ll a, b, c;
	cin >> n >> a >> b >> c;
	vector<ll> arr(n+1), s(n+1), dp(n+1);
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
		s[i] = s[i-1]+arr[i];
	}
	LineContainer cht;
	cht.add(b, 0);
	for(int i=1; i<=n; i++) {
		dp[i] = cht.query(s[i]) + a*s[i]*s[i] + c;
		cht.add(-2*a*s[i]+b, dp[i]+a*s[i]*s[i]-b*s[i]);
	}
	cout << dp[n];
}
