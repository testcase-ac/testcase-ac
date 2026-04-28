#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  vector<pii> edges;
  for (int b = 2; b <= N; b += 2) {
    for (int r = 1; r <= N; r += 2) {
      edges.emplace_back(b, r);
      if (!--K) goto done;
    }
  }

done:
  if (K) cout << "NO\n";
  else {
    cout << "YES\n";
    for (auto [u, v] : edges) cout << u << ' ' << v << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
