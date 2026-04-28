#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 2e3;
int x[MAX + 1], y[MAX + 1];
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

int euclid(int i, int j) {
  int xd = x[i] - x[j];
  int yd = y[i] - y[j];
  return xd * xd + yd * yd;
}

int main() {
  int n, c;
  cin >> n >> c;
  for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
  for (int i = 1; i <= n; i++) parent[i] = i;

  // Kruskal's algorithm
  vector<tuple<int, int, int>> ta;
  for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
    ta.push_back({euclid(i, j), i, j});
  }
  sort(ta.begin(), ta.end());

  ll ans = 0;
  for (auto [w, i, j] : ta) {
    if (w < c) continue;
    if (Find(i) == Find(j)) continue;
    ans += w;
    Union(i, j);
  }

  bool able = true;
  int s = Find(1);
  for (int i = 2; i <= n; i++) able &= s == Find(i);

  if (able) cout << ans << '\n';
  else cout << -1 << '\n';
}
