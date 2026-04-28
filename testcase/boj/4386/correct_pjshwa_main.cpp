#include <bits/stdc++.h>
#define dii pair<double, double>
typedef long long ll;
using namespace std;

const int MAX = 2e3;
dii v[MAX + 1];
int parent[MAX + 1];

double euclid(dii a, dii b) {
  return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
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

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> v[i].first >> v[i].second;
  for (int i = 1; i <= n; i++) parent[i] = i;

  // Kruskal's algorithm
  vector<tuple<double, int, int>> ta;
  for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
    ta.push_back({euclid(v[i], v[j]), i, j});
  }
  sort(ta.begin(), ta.end());

  double ans = 0;
  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    ans += w;
    Union(x, y);
  }

  cout << fixed << setprecision(10) << ans << '\n';
}
