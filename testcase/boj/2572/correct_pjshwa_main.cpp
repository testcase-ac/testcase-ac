#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX];
vector<pii> graph[MAX + 1];
int d[MAX + 1][MAX + 1], n;

int r(int v, int rem) {
  if (rem == n) return 0;
  if (d[v][rem] != -1) return d[v][rem];

  int res = 0;
  for (auto [u, w] : graph[v]) {
    res = max(res, r(u, rem + 1) + (w == a[rem]));
  }

  return d[v][rem] = res;
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    if (s == "R") a[i] = 0;
    if (s == "G") a[i] = 1;
    if (s == "B") a[i] = 2;
  }

  int v, e;
  cin >> v >> e;
  while (e--) {
    int x, y; string s;
    cin >> x >> y >> s;
    if (s == "R") {
      graph[x].push_back({y, 0});
      graph[y].push_back({x, 0});
    }
    if (s == "G") {
      graph[x].push_back({y, 1});
      graph[y].push_back({x, 1});
    }
    if (s == "B") {
      graph[x].push_back({y, 2});
      graph[y].push_back({x, 2});
    }
  }

  memset(d, -1, sizeof d);
  cout << r(1, 0) * 10 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
