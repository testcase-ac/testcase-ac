#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  vector<pii> a(n);
  map<int, int> t;
  for (int i = 0; i < n; i++) {
    cin >> a[i].first;
    a[i].second = i;
    t[a[i].first]++;
  }
  sort(a.begin(), a.end());

  for (auto& [k, v] : t) {
    if (v * 2 > n) return cout << "-1\n", void();
  }

  int res[n];
  for (int i = 0; i < n; i++) res[a[i].second] = a[(i + n / 2) % n].first;

  for (int i = 0; i < n; i++) cout << res[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
