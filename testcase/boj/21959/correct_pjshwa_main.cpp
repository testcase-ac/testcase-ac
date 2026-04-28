#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int K; cin >> K;

  int u = 0; vector<pii> T;
  for (int i = 0;; i++) {
    if (u + i < K) {
      u += i;
      T.emplace_back(i, i - 1);
    }
    else {
      T.emplace_back(i, K - u - 1);
      break;
    }
  }

  cout << T.size() << '\n';
  for (auto [a, b] : T) cout << a << ' ' << b << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
