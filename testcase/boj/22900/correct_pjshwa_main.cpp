#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
vector<int> graph[MAX + 1];
int d[MAX + 1], m[MAX + 1], parent[MAX + 1];

int r1(int v) {
  if (d[v] != -1) return d[v];

  int res = 0;
  for (int u : graph[v]) {
    if (u == parent[v]) continue;
    parent[u] = v;
    if (!r1(u)) res++;
  }
  return d[v] = res;
}

int r2(int v) {
  if (m[v] != -1) return m[v];

  int res;
  if (v == 1 || r2(parent[v])) res = 0;
  else res = (r1(v) == 0 && r1(parent[v]) == 1) || (r1(v) && r1(parent[v]) == 0);

  return m[v] = res;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int xi, yi, ai;
    cin >> xi >> yi >> ai;
    graph[xi].push_back(yi);
    graph[yi].push_back(xi);
  }

  memset(d, -1, sizeof(d));
  memset(m, -1, sizeof(m));
  r1(1);

  for (int i = 1; i <= n; i++) {
    if (r1(i) || r2(i)) cout << "Zeze\n";
    else cout << "Portuga\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
