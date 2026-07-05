#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e6;
int T[MAXV + 1];

void rec(int n, int m) {
  if (n > m) swap(n, m);

  if (n == 1) ++T[m];
  else {
    int hn = n / 2, hm = m / 2;
    rec(hn, hm); rec(hn, m - hm);
    rec(n - hn, hm); rec(n - hn, m - hm);
  }
}

void solve() {
  ll n, m; cin >> n >> m;
  rec(n, m);

  vector<pii> ans;
  for (int v = 1; v <= MAXV; ++v) {
    if (T[v] == 0) continue;
    ans.emplace_back(v, T[v]); T[v] = 0;
  }

  cout << ans.size() << '\n';
  for (auto [v, cnt] : ans) cout << v << ' ' << cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
