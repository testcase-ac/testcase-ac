#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, MOD = 1e9 + 7;
int a[MAX], t[7];
bool ban[7];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i], t[a[i] % 7]++;

  int pmod = 0, umod, psum = 0, tcnt = n;
  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    umod = (7 - (pmod + x) % 7) % 7;
    if (t[umod] == tcnt) continue;

    pmod = (pmod + x) % 7;
    psum = (psum + x) % MOD;
    tcnt -= t[umod];
    t[umod] = 0;
    ban[umod] = true;
  }

  cout << tcnt << '\n';
  for (int i = 0; i < n; i++) {
    if (ban[a[i] % 7]) continue;
    cout << (a[i] + psum) % MOD << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
