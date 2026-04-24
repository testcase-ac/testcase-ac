#include <bits/stdc++.h>
using namespace std;
const int MX = 1e4;
int dp[MX];
int f(int t) {
	if(t == 6174) return 0;
	if(dp[t] != -1) return dp[t];
	string s = to_string(t);
	while(s.size() < 4) s = '0' + s;
	sort(s.begin(), s.end());
	int mn = stoi(s), mx;
	reverse(s.begin(), s.end());
	mx = stoi(s);
	int res = f(mx-mn)+1;
	dp[t] = res;
	return res;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(dp, -1, sizeof dp);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		cout << f(t) << '\n';
	}
}
