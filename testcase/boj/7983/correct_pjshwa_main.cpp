#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

void solve() {
  int n;
  cin >> n;

  vector<pii> a(n);
  for (int i = 0; i < n; i++) cin >> a[i].second >> a[i].first;
  sort(a.begin(), a.end());
  reverse(a.begin(), a.end());

  int etime = INF;
  for (int i = 0; i < n; i++) {
    auto [si, ti] = a[i];
    etime = min(etime, si);
    etime -= ti;
  }

  cout << etime << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
