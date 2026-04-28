#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
int B[MAX + 10][MAX + 10], P[MAX + 10][MAX + 10];
int R, C, H, W;

bool check(int m) {
  for (int i = 1; i <= R; ++i) for (int j = 1; j <= C; ++j) {
    P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + (B[i][j] <= m);
  }

  for (int i = H; i <= R; ++i) for (int j = W; j <= C; ++j) {
    int cnt = P[i][j] - P[i - H][j] - P[i][j - W] + P[i - H][j - W];
    if (cnt * 2 >= H * W) return true;
  }
  return false;
}

void solve() {
  cin >> R >> C >> H >> W;
  for (int i = 1; i <= R; ++i) for (int j = 1; j <= C; ++j) cin >> B[i][j];

  int l = 1, r = R * C + 1;
  while (l < r) {
    int m = (l + r) / 2;
    if (check(m)) r = m;
    else l = m + 1;
  }
  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
