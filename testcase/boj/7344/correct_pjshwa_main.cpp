#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
bitset<MAX> vis;

void solve() {
  int n;
  cin >> n;

  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
  sort(a.begin(), a.end());
  vis.reset();

  int cuts = 0;
  for (int i = 0; i < n; i++) {
    if (vis[i]) continue;
    cuts++;

    int last = -1;
    for (int j = i; j < n; j++) {
      if (!vis[j] && a[j].second >= last) vis[j] = 1, last = a[j].second;
    }
  }

  cout << cuts << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
