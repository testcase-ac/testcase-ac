#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, x, xsum = 0; cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> x;
    if (x % 4 == 0) xsum ^= (x - 1);
    else if (x % 4 == 3) xsum ^= (x + 1);
    else xsum ^= x;
  }
  if (xsum == 0) cout << "cubelover\n";
  else cout << "koosaga\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
