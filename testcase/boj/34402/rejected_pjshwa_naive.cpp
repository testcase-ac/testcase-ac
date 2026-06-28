#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
ll N, K, dp[MAXN + 1][4], T[4];

int rec(int i, int t) {
  if (dp[i][t] != -1) return dp[i][t];
  if (i == N) return dp[i][t] = 0;

  int ret = 0, nt = (t + 1) % 4;
  for (int z = 1; z <= K; ++z) {
    if (i + z > N) break;
    ret |= (rec(i + z, nt) ^ (T[t] != T[nt]));
  }
  return dp[i][t] = ret;
}

void solve_N1() {
  return cout << "(2,3) (2,4) (3,4)\n", void();
}

void solve_N2() {
  return cout << "(1,3) (1,4) (3,4)\n", void();
}

void solve_KoverN() {
  return cout << "(1,2) (1,3) (1,4)\n", void();
}

void solve() {
  cin >> N >> K;

  for (int j1 = 0; j1 < 4; ++j1) for (int j2 = j1 + 1; j2 < 4; ++j2) {
    memset(T, 0, sizeof T);
    T[j1] = 1, T[j2] = 1;

    memset(dp, -1, sizeof dp);
    if (rec(1, 0) == (j1 == 0)) cout << "(" << j1 + 1 << "," << j2 + 1 << ") ";
  }
  cout << "\n";

}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
