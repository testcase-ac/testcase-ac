#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
int D[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;

  fill(D + 1, D + n, INF);
  priority_queue<tii> pq;
  while (m--) {
    int i, d, c;
    cin >> i >> d >> c;
    pq.push({c, d, i});
  }

  vector<pii> queries; int q; cin >> q;
  for (int i = 0; i < q; i++) {
    int w;
    cin >> w;
    queries.push_back({w, i});
  }
  sort(queries.begin(), queries.end());
  reverse(queries.begin(), queries.end());

  vector<int> ans(q); int f = 0, sum = 0;
  for (auto [w, qi] : queries) {
    while (!pq.empty()) {
      auto [c, d, i] = pq.top();
      if (c < w) break;

      pq.pop();
      if (D[i] == INF) {
        f++;
        D[i] = d;
        sum += d;
      }
      else if (d < D[i]) {
        sum -= D[i] - d;
        D[i] = d;
      }
    }

    if (f == n - 1) ans[qi] = sum;
    else ans[qi] = -1;
  }

  for (int i = 0; i < q; i++) {
    if (ans[i] == -1) cout << "impossible\n";
    else cout << ans[i] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
