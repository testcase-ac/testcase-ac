#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int c[MAX][MAX];
int parent[MAX + 1];

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
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) parent[i] = i;

  vector<tuple<int, int, int>> ta;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    int w;
    cin >> w;
    ta.push_back({w, i, j});
  }
  sort(ta.begin(), ta.end());

  ll ans = 0;
  for (auto [w, i, j] : ta) {
    if (Find(i) == Find(j)) continue;
    ans += w;
    Union(i, j);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
