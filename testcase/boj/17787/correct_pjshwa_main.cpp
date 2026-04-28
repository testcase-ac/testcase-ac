#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<int> ans;

void investigate(int tc) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];

  set<int> w;
  priority_queue<pii> e;
  for (int i = 0; i < n; ++i) e.emplace(a[i], i);

  bool found = false;
  for (int i = 0; i < n - 1; ++i) {
    while (e.top().second <= i) e.pop();

    auto it = w.upper_bound(a[i]);
    if (it != w.end() && *it < e.top().first) {
      found = true;
      break;
    }
    w.insert(a[i]);
  }

  if (found) ans.push_back(tc);
}

int main() {
  fast_io();

  int t;
  cin >> t;
  for (int tc = 1; tc <= t; ++tc) investigate(tc);

  cout << ans.size() << '\n';
  for (int i = 0; i < ans.size(); ++i) cout << ans[i] << '\n';
}
