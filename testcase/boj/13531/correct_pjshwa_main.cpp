#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
ll d[MAX];

void solve() {
  int n;
  cin >> n;

  if (n > 15) return cout << "0.6321205588\n", void();

  d[1] = 0, d[2] = 1;
  for (int i = 3; i <= n; i++) {
    d[i] = (i - 1) * (d[i - 1] + d[i - 2]);
  }

  ll f = 1;
  for (int i = 2; i <= n; i++) f *= i;

  cout << fixed << setprecision(10) << (double)(f - d[n]) / f << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
