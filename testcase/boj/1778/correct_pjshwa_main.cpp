#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e4;
vector<pii> graph[MAX + 1];
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

int n, m, tc;
void solve() {
  for (int i = 1; i <= n; i++) parent[i] = i;
  while (m--) {
    int a, b;
    cin >> a >> b;
    Union(a, b);
  }

  set<int> u;
  for (int i = 1; i <= n; i++) u.insert(Find(i));
  cout << "Case " << ++tc << ": " << u.size() << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> m;
    if (n == 0 && m == 0) break;
    solve();
  }
}
