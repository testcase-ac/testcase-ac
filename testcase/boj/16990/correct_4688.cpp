#include <bits/stdc++.h>
using namespace std;
#define int long long
string wall[10001];
int buk[60][60];
int mod60(int t) {
	if(t < 0) t += 60ll * INT_MAX;
	t %= 60;
	return t;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++) {
		int t;
		cin >> t >> wall[i];
	}
	while(m--) {
		int p, d;
		cin >> p >> d;
		buk[mod60(p)][mod60(d)]++;
	}
	for(int i=1; i<=n; i++) {
		for(int p=0; p<60; p++) {
			for(int d=0; d<60; d++) {
				if(wall[i][(p+d*i)%wall[i].size()] == '0') {
					buk[p][d] = 0;
				}
			}
		}
	}
	int ans = 0;
	for(int i=0; i<60; i++) {
		for(int j=0; j<60; j++) {
			ans += buk[i][j];
		}
	}
	cout << ans;
}
