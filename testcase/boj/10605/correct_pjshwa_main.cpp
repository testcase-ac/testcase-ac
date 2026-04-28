#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300;
int parent[MAX + 1];
vector<pii> compo[MAX + 1];
int n, m, k;

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
  for (int i = 1; i <= n; i++) parent[i] = i, compo[i].clear();

  while (m--) {
    int u, v;
    cin >> u >> v;
    Union(u, v);
  }

  set<int> cs;
  while (k--) {
    int ci, si, ni;
    cin >> ci >> si >> ni;
    compo[Find(ci)].push_back({si, ni});
    cs.insert(Find(ci));
  }

  int ans = 0;
  for (int c : cs) {
    int left = 1, right = 1e5 + 10;
    while (left < right) {
      int mid = (left + right) / 2, u = mid;

      for (auto [si, ni] : compo[c]) {
        if (ni < mid) continue;
        else u -= si;
      }

      if (u >= 0) right = mid;
      else left = mid + 1;
    }
    ans += left;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> m >> k;
    if (n == 0 && m == 0 && k == 0) break;
    solve();
  }
}
