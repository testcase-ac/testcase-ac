#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int parent[MAX + 1], s[MAX + 1];
bool ban[MAX + 1];

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
  ll n, m, k;
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
    parent[i] = i;
  }

  while (m--) {
    int a, b;
    cin >> a >> b;
    if (a > b) swap(a, b);
    
    if (a == 1 && b == n) ban[b] = true;
    else ban[a] = true;
  }

  for (int i = 1; i <= n; i++) {
    if (ban[i]) continue;
    if (i == n) Union(1, n);
    else Union(i, i + 1);
  }

  map<int, int> cmap;
  for (int i = 1; i <= n; i++) {
    if (cmap.count(Find(i))) cmap[Find(i)] = min(cmap[Find(i)], s[i]);
    else cmap[Find(i)] = s[i];
  }

  ll ans = 0;
  for (auto& [k, v] : cmap) ans += v;

  if (cmap.size() <= 1 || ans <= k) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
