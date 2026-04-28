#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5, MAXV = 100;
int c[MAX];
vector<int> graph[MAX];
double d[MAX][MAXV];
double p[MAXV];

double r(int v, int w) {
  if (d[v][w] != -1) return d[v][w];
  if (graph[v].empty()) return d[v][w] = p[w] * c[v];

  double ret = 0;
  for (int u : graph[v]) {
    ret = max(ret, r(u, w));

    // Eat pizza here
    if (w < MAXV - 1) ret = max(ret, r(u, w + 1) + p[w] * c[v]);
  }

  return d[v][w] = ret;
}

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> c[i];
    fill(d[i], d[i] + MAXV, -1);
  }
  while (m--) {
    int u, v; cin >> u >> v;
    graph[u].push_back(v);
  }

  p[0] = 1;
  for (int i = 1; i < MAXV; i++) p[i] = p[i - 1] / 2;

  cout << fixed << setprecision(10) << r(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
