#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int s[MAX], p[MAX];
int d[2][100'001];

void solve() {
  int n, m, sum = 0;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> s[i] >> p[i], sum += s[i];

  // 0-1 Knapsack
  for (int i = 1; i <= n; i++) {
    int x = i % 2, price = p[i - 1];
    for (int j = m; j >= 0; j--) {
      d[x][j] = d[x ^ 1][j];
      if (j >= price) d[x][j] = max(d[x][j], d[x ^ 1][j - price] + s[i - 1]);
      if (j >= price + 1) d[x][j] = max(d[x][j], d[x ^ 1][j - price - 1] + 2 * s[i - 1]);
    }
  }

  int msum = d[n % 2][m];
  if (msum > sum) cout << "W\n";
  else if (msum == sum) cout << "D\n";
  else cout << "L\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
