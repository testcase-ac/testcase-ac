#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;
  vector<pii> A;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    A.emplace_back(x, y);
  }
  
  int l = 0, r = 1e9 + 1;
  while (l < r) {
    int m = (l + r) / 2;

    int cnt = 0;
    for (auto& [x, y] : A) {
      cnt += x + m >= y;
    }

    if (cnt < K) l = m + 1;
    else r = m;
  }

  cout << l << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
