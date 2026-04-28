#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
int a[MAX], n;
bool d[MAX];

bool reachable(ll k) {
  memset(d, 0, sizeof(d));
  d[0] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (d[j] && (ll)(i - j) * (1 + abs(a[i] - a[j])) <= k) d[i] = 1;
    }
  }
  return d[n - 1];
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];

  ll left = 1, right = 1e10;
  while (left < right) {
    ll mid = (left + right) / 2;
    if (reachable(mid)) right = mid;
    else left = mid + 1;
  }
  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
