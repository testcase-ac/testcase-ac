#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, INF = 0x3f3f3f3f;
const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int B[MAXN + 1][MAXN + 1], V[MAXN + 1][MAXN + 1];

void solve() {
  int N = 1000;
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) {
    B[i][j] = (i + j - 1) * (i + j - 2) / 2 + i;
  }

  auto oob = [&](int i, int j) {
    return i < 1 || i > N || j < 1 || j > N;
  };

  int ci = 1, cj = 1; V[ci][cj] = 1;
  vector<int> traj{B[ci][cj]};

  while (1) {
    int ni = ci, nj = cj, nv = INF;
    for (int k = 0; k < 8; ++k) {
      int ti = ci + dx[k], tj = cj + dy[k];
      if (oob(ti, tj) || V[ti][tj]) continue;
      if (B[ti][tj] < nv) ni = ti, nj = tj, nv = B[ti][tj];
    }
    if (ni == ci && nj == cj) break;
    ci = ni, cj = nj; V[ci][cj] = 1;
    traj.push_back(B[ci][cj]);
  }

  int k; cin >> k;
  cout << traj[k] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
