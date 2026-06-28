#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, MAXT = 1e6;
queue<int> R[MAXN], W[MAXN + 1]; int T[MAXN];

void solve() {
  int n, m; cin >> n >> m;

  int tot = 0;
  for (int i = 0; i < n; ++i) {
    int k; cin >> T[i] >> k;
    tot += k;
    while (k--) {
      int x; cin >> x;
      R[i].push(x);
    }
  }

  int ans = 0; vector<pii> S;
  for (int t = 0; tot; ++t) {
    for (int j = 1; j <= m; ++j) {
      if (W[j].empty()) continue;
      int p = W[j].front(); W[j].pop();
      ans = max(ans, t); --tot;

      if (R[p].empty()) continue;
      int q = R[p].front(); R[p].pop();
      S.emplace_back(p, q);
    }

    for (int p = 0; p < n; ++p) {
      if (t != T[p]) continue;
      int q = R[p].front(); R[p].pop();
      S.emplace_back(p, q);
    }

    sort(S.begin(), S.end(), greater<>());
    while (!S.empty()) {
      auto [p, q] = S.back(); S.pop_back();
      W[q].push(p);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
