#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 2e3;
int v[MAX + 1];
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

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> v[i];
  for (int i = 1; i <= n; i++) parent[i] = i;

  // Kruskal's algorithm
  vector<tuple<int, int, int>> ta;
  for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
    ta.push_back({-(v[i] ^ v[j]), i, j});
  }
  sort(ta.begin(), ta.end());

  ll ans = 0;
  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    ans += w;
    Union(x, y);
  }

  cout << -ans << '\n';
}
