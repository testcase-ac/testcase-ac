#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAX = 1e6;
int parent[MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) parent[i] = i;
  vector<pii> a(m), s;
  for (int i = 0; i < m; i++) cin >> a[i].first >> a[i].second;
  sort(a.begin(), a.end());

  for (auto& [as, ae] : a) {
    if (s.empty() || s.back().second < as) s.push_back({as, ae});
    else s.back().second = max(ae, s.back().second);
  }

  for (auto& [ss, se] : s) {
    for (int i = ss; i < se; i++) Union(i, i + 1);
  }

  set<int> u;
  for (int i = 1; i <= n; i++) u.insert(Find(i));

  cout << u.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
