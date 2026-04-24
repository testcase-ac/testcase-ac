#include <bits/stdc++.h>
using namespace std;
const int MX = 1e6+3, MOD = 1e9+7;
typedef long long ll;
ll coef[200001][301], dp[200001];
int nodes[MX][27];
string arr;
int nxt = 1;
ll ans;
void add_trie(string &s) {
	int cur = 0;
	for(int i=0; i<s.size(); i++) {
		int t = s[i]-'a';
		if(!nodes[cur][t]) {
			nodes[cur][t] = nxt++;
		}
		cur = nodes[cur][t];
		nodes[cur][26]++;
	}
}
void count_coef(int l, int r, int mx) { // [l, r]
	int cur = 0;
	for(int i=l; i<=r && i < mx; i++) {

		int t = arr[i]-'a';
		if(!nodes[cur][t]) {
			break;
		}
		cur = nodes[cur][t];
		coef[i][i-l+1] += nodes[cur][26];
		coef[i][i-l+1] %= MOD;
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n--) {
		string tmp;
		cin >> tmp;
		add_trie(tmp);
	}
	cin >> arr;
	n = arr.size();
	for(int i=0; i<n; i++) {
		count_coef(i, i+299, n);
	}
	for(int i=0; i<n; i++) {
		for(int j=1; j<=300; j++) {
			if(i - j == -1) {
				dp[i] += coef[i][j];
				break;
			}
			dp[i] += dp[i-j]*coef[i][j];
			dp[i] %= MOD;
		}
	}
	cout << dp[n-1];
}
