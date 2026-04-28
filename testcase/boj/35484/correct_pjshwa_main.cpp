#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int ask(int a, int b, int d) {
  cout << "? " << a << ' ' << b << ' ' << d << endl;
  int res; cin >> res;
  return res;
}

void solve() {
  int N; cin >> N;
  int l = 1, r = N / 2 + 1;
  while (l < r) {
    int m = (l + r) / 2;
    if (ask(0, N, m) > 0) r = m;
    else l = m + 1;
  }
  int ans = 2 * l;
  if (ask(1, N, l - 1) > 0) --ans;
  cout << "! " << ans << endl;
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
