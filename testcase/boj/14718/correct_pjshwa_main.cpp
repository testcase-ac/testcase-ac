#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, k;
  cin >> n >> k;

  vector<int> e1, e2, e3;
  vector<tii> estats;
  for (int i = 0; i < n; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    e1.push_back(a);
    e2.push_back(b);
    e3.push_back(c);
    estats.push_back(make_tuple(a, b, c));
  }

  int ans = 1e9 + 7;
  for (int s1 : e1) for (int s2 : e2) for (int s3 : e3) {
    int cnt = 0;
    for (auto [a, b, c] : estats) {
      if (s1 >= a && s2 >= b && s3 >= c) ++cnt;
    }
    if (cnt >= k) ans = min(ans, s1 + s2 + s3);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
