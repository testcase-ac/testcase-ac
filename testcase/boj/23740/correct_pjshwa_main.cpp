#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

void solve() {
  int n;
  cin >> n;
  vector<tii> v(n);
  for (int i = 0; i < n; i++) {
    int s, e, c;
    cin >> s >> e >> c;
    v[i] = {s, e, c};
  }
  sort(v.begin(), v.end());

  vector<tii> ans;
  auto [cs, ce, cc] = v[0];
  for (int i = 1; i < n; i++) {
    auto [s, e, c] = v[i];
    if (s <= ce) {
      cc = min(cc, c);
      ce = max(ce, e);
    }
    else {
      ans.push_back({cs, ce, cc});
      cs = s;
      ce = e;
      cc = c;
    }
  }
  ans.push_back({cs, ce, cc});

  cout << ans.size() << '\n';
  for (auto [s, e, c] : ans) {
    cout << s << ' ' << e << ' ' << c << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
