#include <bits/stdc++.h>
using namespace std;
pair<int, int> pos[100];
int n, l, m;
int count(int r, int c, int a, int b) {
	int cnt = 0;
	for(int i=0; i<m; i++) {
		if(r <= pos[i].first && pos[i].first <= r+a && c <= pos[i].second && pos[i].second <= c+b)
		cnt++;
	}
	return cnt;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> l >> m;
	for(int i=0; i<m; i++) {
		cin >> pos[i].first >> pos[i].second;
	}
	l /= 2;
	int ans = 0;
	for(int i=0; i<m; i++) {
		for(int j=1; j<l; j++) {
			for(int k=0; k<=l-j; k++) {
				ans = max(ans, count(pos[i].first, pos[i].second-k, j, l-j));			
			}
		}
	}
	cout << ans;
}
