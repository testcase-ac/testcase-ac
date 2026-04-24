#include <bits/stdc++.h>
using namespace std;
#define int long long
string chr = "RPS";
string dp[13][3];
string f(int i, int j) {
	if(!i)
		return chr.substr(j, 1);
	string a, b;
	if(j == 0) {
		a = f(i-1, 0);
		b = f(i-1, 2);
	} else if(j == 1) {
		a = f(i-1, 1);
		b = f(i-1, 0);
	} else if(j == 2) {
		a = f(i-1, 2);
		b = f(i-1, 1);
	}
	if(a > b)
		swap(a, b);
	return a + b;
}
vector<int> counts(string& s) {
	vector<int> cnt(3);
	for(char c: s) {
		if(c == 'R')
			cnt[0]++;
		else if(c == 'P')
			cnt[1]++;
		else if(c == 'S')
			cnt[2]++;
	}
	return cnt;
}
void solve() {
	int N;
	vector<int> cnt(3);
	cin >> N;
	for(int i=0; i<3; i++) {
		cin >> cnt[i];
	}
	string r = f(N, 0), p = f(N, 1), s = f(N, 2);
	if(counts(r) == cnt) {
		cout << r << '\n';
	} else if(counts(p) == cnt) {
		cout << p << '\n';
	} else if(counts(s) == cnt) {
		cout << s << '\n';
	} else {
		cout << "IMPOSSIBLE\n";
	}
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	for(int t=1; t<=T; t++) {
		cout << "Case #" << t << ": ";
		solve();
	}
}
