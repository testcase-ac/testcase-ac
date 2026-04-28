#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
int c2[MAX + 1], c5[MAX + 1];
int d2[MAX + 1], d5[MAX + 1];

void solve() {
  int n, k;
  cin >> n >> k;
  memset(c2, 0, sizeof(c2));
  memset(c5, 0, sizeof(c5));

  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    while (x % 2 == 0) x /= 2, c2[i]++;
    while (x % 5 == 0) x /= 5, c5[i]++;
  }

  fill(d2, d2 + n + 1, INF);
  fill(d5, d5 + n + 1, INF);
  d2[1] = c2[1], d5[1] = c5[1];
  for (int i = 2; i <= n; i++) {
    for (int w = 1; w <= k; w++) {
      if (w >= i) break;
      d2[i] = min(d2[i], d2[i - w] + c2[i]);
      d5[i] = min(d5[i], d5[i - w] + c5[i]);
    }
  }

  cout << min(d2[n], d5[n]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
