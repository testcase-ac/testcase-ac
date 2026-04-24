#include <bits/stdc++.h>
using namespace std;

int cnt[2][101], tmp[2][101];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n--) {
		int x, y;
		cin >> x >> y;
		cnt[0][x]++, cnt[1][y]++;
		memcpy(tmp, cnt, sizeof tmp);
		int i = 1, j = 100, ans = 0, t;
		while(1) {
			while(i <= 100 && !tmp[0][i]) i++;
			while(j && !tmp[1][j]) j--;
			if(!j) break;
			ans = max(ans, i+j);
			t = min(tmp[0][i], tmp[1][j]);
			tmp[0][i] -= t;
			tmp[1][j] -= t;
		}
		cout << ans << '\n';
	}
}
