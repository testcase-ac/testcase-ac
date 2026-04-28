#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int d[MAX + 1];

void solve() {
  memset(d, 0, sizeof(d));

  int n, val;
  cin >> n;
  vector<int> coins(n);
  for (int i = 0; i < n; i++) cin >> coins[i];
  cin >> val;

  d[0] = 1;
  for (int coin : coins) for (int w = 0; w <= MAX; w++) {
    if (w >= coin) d[w] += d[w - coin];
  }
  cout << d[val] << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
