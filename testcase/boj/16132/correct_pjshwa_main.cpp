#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2500;
ll d[51][MAX + 1];

void solve() {
  int n;
  cin >> n;
  int sum = n * (n + 1) / 2;
  if (sum & 1) return cout << "0\n", void();

  d[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int w = 0; w <= MAX; w++) d[i][w] = d[i - 1][w];
    for (int w = 0; w <= MAX; w++) {
      if (w - i >= 0) d[i][w] += d[i - 1][w - i];
    }
  }

  cout << d[n][sum / 2] / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
