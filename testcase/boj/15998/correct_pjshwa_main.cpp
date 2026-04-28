#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
ll a[MAX], b[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i] >> b[i];

  ll cur = 0, g = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] < 0 && cur + a[i] < b[i]) {
      ll addend = b[i] - (cur + a[i]);
      g = __gcd(g, addend);
    }
    cur = b[i];
  }

  cur = 0;
  for (int i = 0; i < n; i++) {
    if (cur + a[i] < 0) {
      ll addend = -(cur + a[i]);
      ll tries = (addend - 1) / g + 1;
      cur += tries * g;
    }

    cur += a[i];
    if (cur != b[i]) return cout << "-1\n", void();
  }

  if (g == 0) g = 1;
  cout << g << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
