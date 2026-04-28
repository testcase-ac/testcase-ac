#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
ll d[MAX];

void solve() {
  int n;
  cin >> n;
  vector<tuple<int, int, int>> info;
  vector<int> eps;
  for (int i = 0; i < n; i++) {
    int s, e, a;
    cin >> s >> e >> a;
    info.emplace_back(e, s, a);
    eps.push_back(e);
  }
  sort(info.begin(), info.end());
  sort(eps.begin(), eps.end());

  for (int et = 0; et < n; et++) {
    if (et) d[et] = d[et - 1];
    auto [ce, cs, ca] = info[et];
    auto it = upper_bound(eps.begin(), eps.end(), cs);
    if (it == eps.begin()) d[et] = max(d[et], (ll)ca);
    else d[et] = max(d[et], d[it - 1 - eps.begin()] + ca);
  }

  cout << d[n - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
