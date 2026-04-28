#include <bits/stdc++.h>
#define ll long long
using namespace std;

int parent[10001];

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

int main() {
  int v, e, a, b, c;
  cin >> v >> e;

  for (int i = 1; i <= v; i++) parent[i] = i;

  // Kruskal's algorithm
  vector<tuple<int, int, int>> ta;
  for (int i = 0; i < e; i++) {
    cin >> a >> b >> c;
    ta.push_back({c, a, b});
  }
  sort(ta.begin(), ta.end());

  ll ans = 0;
  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    ans += w;
    Union(x, y);
  }

  cout << ans << '\n';
}
