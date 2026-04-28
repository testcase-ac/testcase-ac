#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, ans = 0; cin >> N;
  for (int i = 0; i < N; ++i) {
    int ok = 0, si, ci, ai, ri; cin >> si >> ci >> ai >> ri;
    if (si >= 1000) ok = 1;
    if (ci >= 1600) ok = 1;
    if (ai >= 1500) ok = 1;
    if (ri != -1 && ri <= 30) ok = 1;
    ans += ok;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
