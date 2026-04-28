#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

void solve() {
  int N;
  cin >> N;
  
  multiset<int> as;
  vector<tii> iv1;
  vector<pii> iv2;
  for (int i = 0; i < N; i++) {
    int a, x, y;
    cin >> a >> x >> y;
    as.insert(a);
    iv1.push_back({a, x, y});
  }

  for (auto [a, x, y] : iv1) {
    as.erase(as.find(a));
    if (as.upper_bound(x - 1) == as.upper_bound(y)) iv2.push_back({x, y});
    as.insert(a);
  }

  sort(iv2.begin(), iv2.end());

  set<int> u = {as.begin(), as.end()};
  int ans = u.size();

  pii cur = {-INF, INF};
  for (auto [x, y] : iv2) {
    auto& [cx, cy] = cur;
    if (cy >= x) {
      cx = max(x, cx);
      cy = min(y, cy);
    }
    else {
      ans++;
      cx = x;
      cy = y;
    }
  }

  if (cur.first != -INF) ans++;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
