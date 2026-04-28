#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 30;
int parent[MAX + 1];
int n;

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
  for (int i = 0; i < n; i++) parent[i] = i;

  // Kruskal's algorithm
  vector<tuple<int, int, int>> ta;
  for (int i = 0; i < n - 1; i++) {
    string o;
    int k;
    cin >> o >> k;
    while (k--) {
      string d;
      int di;
      cin >> d >> di;
      ta.push_back(make_tuple(di, o[0] - 'A', d[0] - 'A'));
    }
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

int main() {
  while (1) {
    cin >> n;
    if (!n) break;
    solve();
  }
}
