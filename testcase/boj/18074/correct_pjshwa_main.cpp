#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5, INF = 0x3f3f3f3f;
ll a[MAX + 1];

void solve() {
  int n;
  cin >> n;

  ll maxx = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    maxx = max(maxx, a[i]);
    a[i] += a[i - 1];
  }

  int q;
  cin >> q;
  vector<pii> queries(q);
  vector<int> ans(q);
  for (int i = 0; i < q; i++) {
    int x;
    cin >> x;
    queries[i] = {x, i};
  }
  sort(queries.begin(), queries.end());

  map<int, int> s;
  for (int i = 0; i < q; i++) s[queries[i].first] = -1;

  for (auto [x, _] : s) {
    if (x < maxx) continue;

    int cur = 0, ci = 0, cnt = 0;
    while (ci < n + 1) {
      auto it = lower_bound(a + ci, a + n + 1, cur + x);
      cnt++;
      if (*it - cur == x) it++;
      cur = *(it - 1);
      ci = it - a;
    }
    s[x] = cnt;
  }

  for (int i = 0; i < q; i++) {
    auto& [x, j] = queries[i];
    ans[j] = s[x];
  }

  for (int i = 0; i < q; i++) {
    if (ans[i] == -1) cout << "Impossible\n";
    else cout << ans[i] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
