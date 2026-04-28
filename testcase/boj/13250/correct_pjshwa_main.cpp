#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
double d[MAX + 1];

void solve() {
  int n;
  cin >> n;
  
  d[0] = 0;
  for (int i = 1; i <= n; i++) {
    double cur = 0;
    for (int j = 1; j <= 6; j++) {
      if (i - j < 0) break;
      cur += d[i - j] / 6;
    }
    d[i] = cur + 1;
  }

  cout << fixed << setprecision(10) << d[n] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
