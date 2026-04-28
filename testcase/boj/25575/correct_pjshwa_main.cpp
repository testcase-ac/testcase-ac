#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, K; cin >> N >> M >> K;

  vector<int> deg_x(N), deg_y(M);
  vector<pii> edges;
  for (int i = 0; i < K; ++i) {
    int u, v; cin >> u >> v; --u; --v;
    edges.emplace_back(u, v);
    ++deg_x[u]; ++deg_y[v];
  }

  vector<int> deg_x_s = deg_x, deg_y_s = deg_y;
  sort(deg_x_s.begin(), deg_x_s.end());
  sort(deg_y_s.begin(), deg_y_s.end());

  ll acc = 0;
  for (int i = 0; i < N; ++i) acc += deg_x_s[i] * (i + 1);
  for (int i = 0; i < M; ++i) acc += deg_y_s[i] * (i + 1);

  ll maxr = 0;
  for (auto [u, v] : edges) {
    int xi = lower_bound(deg_x_s.begin(), deg_x_s.end(), deg_x[u]) - deg_x_s.begin();    
    int yi = lower_bound(deg_y_s.begin(), deg_y_s.end(), deg_y[v]) - deg_y_s.begin();
    maxr = max(maxr, acc - xi - yi - 2);
  }

  cout << acc << ' ' << maxr << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
