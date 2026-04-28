#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000, MAXQ = 2e5;
int dp[MAXN][MAXN][3], a[MAXN], d[MAXQ], s[MAXQ];
int m[MAXN][MAXN];

void solve() {
  int n, q; cin >> n >> q;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < q; i++) cin >> d[i] >> s[i];

  for (int i = 0; i < n; i++) {
    m[i][i] = a[i];
    for (int j = i + 1; j < n; j++) m[i][j] = min(m[i][j - 1], a[j]);
  }

	int lij, des, tren;
  for (int g = n - 1; g >= 0; g--) for (int l = 0; l < n; l++) {
    int r = l + g;
    if (r >= n) break;



			if(j && a[j - 1] >= val[dp[j - 1][j + i][0]]) {
				lij = dp[j - 1][j + i][1] + 1;
			}
			else {
				lij = 0;
			}
			if(j + i < n && a[j + i] >= val[dp[j][j + i + 1][0]]) {
				des = dp[j][j + i + 1][2] + 1;
			}
			else {
				des = 0;
			}
			if(!j) {
				tren = dp[j][j + i + 1][0];
				if(des == d[tren]) {
					tren++;
					des = 0;
				}
				dp[j][j + i][0] = tren;
				dp[j][j + i][1] = 0;
				dp[j][j + i][2] = des;
				continue;
			}
			tren = max(dp[j][j + i + 1][0], dp[j - 1][j + i][0]);
			if(tren != dp[j][j + i + 1][0]) {
				des = 0;
			}
			if(tren != dp[j - 1][j + i][0]) {
				lij = 0;
			}
			if(lij == d[tren] || des == d[tren]) {
				lij = 0;
				des = 0;
				tren++;
			}
			dp[j][j + i][0] = tren;
			dp[j][j + i][1] = lij;
			dp[j][j + i][2] = des;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
