#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const double EPS = 1e-5;
vector<tii> graph[MAX + 1];
double c[MAX + 1], req[MAX + 1];

void dfs(int v, double l) {
  c[v] = l;
  for (auto& [u, p, s] : graph[v]) {
    double nxt = l * p / 100.0;
    if (s) nxt *= nxt;
    dfs(u, nxt);
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int x, y, p, s;
    cin >> x >> y >> p >> s;
    graph[x].emplace_back(y, p, s);
  }
  for (int i = 1; i <= n; i++) cin >> req[i];

  double left = 0, right = 2e9 + 1;
  while (right - left > EPS) {
    fill(c, c + MAX + 1, 0);

    double mid = (left + right) / 2;
    dfs(1, mid);

    bool able = true;
    for (int i = 1; i <= n; i++) able &= req[i] <= c[i];

    if (able) right = mid;
    else left = mid + EPS;
  }

  cout << fixed << setprecision(10) << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
