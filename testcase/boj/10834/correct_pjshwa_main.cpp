#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  ll op = 0, w = 1;
  for (int i = 0; i < N; ++i) {
    int a, b, s; cin >> a >> b >> s;
    op ^= s; w /= a; w *= b;
  }
  cout << op << ' ' << w << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
