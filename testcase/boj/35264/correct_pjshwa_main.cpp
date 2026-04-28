#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int A[MAXN + 5];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  ll D[4]{}; vector<tuple<int, int, int>> ans;
  for (int i = 1; i <= N; ++i) {
    int m = i % 4;

    ll d = A[i] - D[m];
    if (d == 0) continue;

    if (d > 0) ans.emplace_back(i, d, 3);
    else ans.emplace_back(i, -d, 1);
    D[m] += d; D[(m + 2) % 4] -= d;
  }

  cout << ans.size() << '\n';
  for (auto& [x, v, p] : ans) cout << x << ' ' << v << ' ' << p << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
