#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
ll d[MAX + 1];

void solve() {
  int n;
  cin >> n;
  vector<tuple<int, int, int>> info;
  for (int i = 0; i < n; i++) {
    int s, e, a;
    cin >> s >> e >> a;
    info.emplace_back(e, s, a);
  }
  sort(info.begin(), info.end());

  int p = 0;
  for (int et = 1; et <= MAX; et++) {
    d[et] = d[et - 1];
    while (p < n && get<0>(info[p]) <= et) {
      auto [ce, cs, ca] = info[p];
      d[et] = max(d[et], d[cs] + ca);
      p++;
    }
  }

  cout << d[MAX] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
