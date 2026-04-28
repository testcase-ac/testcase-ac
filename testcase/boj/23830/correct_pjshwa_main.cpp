#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int t[MAX + 1];

void solve() {
  int n, p, q, r;
  ll s = 0, smax;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    s += x;
    t[x]++;
  }

  cin >> p >> q >> r >> smax;
  for (int i = r + 1; i <= MAX; i++) s -= t[i] * p;

  for (int i = 1; i <= 1e5 + 1; i++) {
    s += t[i - 1] * q;
    s += t[r + i] * p;
    if (s >= smax) {
      cout << i << '\n';
      return;
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
