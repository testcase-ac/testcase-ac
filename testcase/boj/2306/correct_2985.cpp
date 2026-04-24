#include <bits/stdc++.h>
using namespace std;
const int MX = 500;
int dp[MX][MX], ans;
bool ispair(char a, char b) {
	return (a == 'a' && b == 't') || (a == 'g' && b == 'c');
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	cin >> s;
	int n = s.size();
	for(int i=0; i<n-1; i++) {
		if(ispair(s[i], s[i+1]))
			dp[i][i+1] = 2;
	}
	for(int d=2; d<n; d++) {
		for(int i=0; i+d<n; i++) {
			int j = i+d;
			if(ispair(s[i], s[j]))
				dp[i][j] = dp[i+1][j-1] + 2;
			for(int k=i; k<=j; k++) {
				dp[i][j] = max(dp[i][j], dp[i][k]+dp[k+1][j]);
			}
		}
	}
	cout << dp[0][n-1];
}
