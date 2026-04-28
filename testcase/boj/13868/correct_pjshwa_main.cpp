#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, MOD = 1e9 + 7;
pll A[MAX];
int C[MAX + 1][MAX + 1], ans[MAX + 1];

void solve() {
  int N;
  cin >> N;

  set<pll> points;
  map<pll, int> duals, duals_o;
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    A[i] = {2 * x, 2 * y};
    points.insert(A[i]);
  }
  
  for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++) {
    auto [x1, y1] = A[i];
    auto [x2, y2] = A[j];
    ll xh = (x1 + x2) / 2, yh = (y1 + y2) / 2;

    duals[{xh, yh}]++;
    if (points.count({xh, yh})) duals_o[{xh, yh}]++;
  }

  ans[1] = N;
  for (auto [k, v] : duals) {
    auto [x, y] = k;
    for (int c = 1; c <= v; c++) {
      int val = C[v][c];
      ans[2 * c] = (ans[2 * c] + C[v][c]) % MOD;
    }
  }
  for (auto [k, v] : duals_o) {
    auto [x, y] = k;
    for (int c = 1; c <= v; c++) {
      int val = C[v][c];
      ans[2 * c + 1] = (ans[2 * c + 1] + C[v][c]) % MOD;
    }
  }

  for (int i = 1; i <= N; i++) cout << ans[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  for (int i = 0; i <= MAX; i++) C[i][0] = 1;
  for (int i = 1; i <= MAX; i++) for (int j = 1; j <= MAX; j++) {
    C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
