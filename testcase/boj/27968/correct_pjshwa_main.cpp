#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int Q, M; cin >> Q >> M;

  vector<ll> B(M + 1);
  for (int i = 1; i <= M; ++i) cin >> B[i], B[i] += B[i - 1];

  while (Q--) {
    ll x; cin >> x;

    auto it = lower_bound(B.begin(), B.end(), x);
    if (it == B.end()) cout << "Go away!\n";
    else cout << it - B.begin() << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
