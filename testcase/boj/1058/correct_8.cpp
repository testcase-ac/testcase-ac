#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<vector<int>> prev, curr(n, vector<int>(n, 1e9+7));
	for(int i=0; i<n; i++) {
		curr[i][i] = 0;
		string s;
		cin >> s;
		for(int j=0; j<n; j++) {
			if(s[j] == 'Y')
				curr[i][j] = 1;
		}
	}
	for(int k=0; k<n; k++) {
		prev = curr;
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				curr[i][j] = min(curr[i][j], prev[i][k]+prev[k][j]);
			}
		}
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		int cnt = 0;
		for(int j=0; j<n; j++) {
			if(i == j) continue;
			if(curr[i][j] <= 2) cnt++;
		}
		ans = max(ans, cnt);
	}
	cout << ans;
}
