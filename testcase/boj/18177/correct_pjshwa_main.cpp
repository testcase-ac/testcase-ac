#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int a[MAX];
bool u[MAX], v[MAX];

void solve() {
  int n, k;
  cin >> n >> k;

  for (int i = 0; i < n; i++) cin >> a[i], u[i] = 1;

  int ans = 0;
  for (int b = 29; b >= 0; b--) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      v[i] = u[i] && (a[i] & (1 << b)) ? 1 : 0;
      cnt += v[i];
    }

    if (cnt >= k) {
      ans |= (1 << b);
      for (int i = 0; i < n; i++) u[i] = v[i];
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
