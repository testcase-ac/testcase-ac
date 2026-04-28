#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
pii a[MAX];

int main() {
  fast_io();

  int n, x;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i].second >> a[i].first;
  sort(a, a + n);

  set<int> xs;
  unordered_map<int, set<int>> u;
  u[0].insert(-1);

  int zc = 0, oc = 0;
  for (int i = 0; i < n; i++) {
    auto [x, k] = a[i];
    k ? oc++ : zc++;

    u[zc - oc].insert(x);
    xs.insert(x);
  }

  int ans = 0;
  for (auto [_, s] : u) {
    if (s.size() <= 1) continue;

    int lb = *xs.upper_bound(*s.begin());
    int ub = *s.rbegin();
    ans = max(ans, ub - lb);
  }

  cout << ans << '\n';
}
