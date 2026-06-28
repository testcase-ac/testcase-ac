#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
ll W[MAXN + 1], H, C, D, Dc[MAXN + 1];

void dfs(int i, ll pre, ll d) {
  if (i == H + 1) {
    if (d != D) return;
    for (int i = 1; i <= H; ++i) {
      int t = W[i];
      while (t--) {
        if (Dc[i]) cout << "9 ", --Dc[i];
        else cout << "1 ";
      }
      cout << '\n';
    }
    exit(0);
  }

  for (int j = 0; j <= W[i]; ++j) {
    Dc[i] = j;
    ll sum = 9 * j + 1 * (W[i] - j);
    if (sum <= pre) continue;
    dfs(i + 1, sum, d + j);
  }
}

void solve() {
  cin >> H;
  for (int i = 1; i <= H; ++i) cin >> W[i];
  cin >> C >> D;

  dfs(1, -1, 0);
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
