#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;
matrix operator * (const matrix &a, const matrix &b) {
  int n = a.size();
  matrix c(n, vector<ll>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    }
  }
  return c;
}

const int INF = 1e9 + 7;
int cost[14][14];

void solve() {
  int n = 14;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) cost[i][j] = INF;
    }
  }

  cost[0][5] = 1;
  cost[1][0] = cost[1][5] = cost[1][10] = 1;
  cost[2][1] = 1;
  cost[3][2] = 1;
  cost[4][3] = 1;
  cost[5][0] = cost[5][9] = 1;
  cost[6][1] = cost[6][3] = cost[6][7] = cost[6][11] = cost[6][12] = 1;
  cost[7][3] = cost[7][8] = 1;
  cost[8][3] = cost[8][4] = 1;
  cost[9][10] = 1;
  cost[10][6] = cost[10][11] = 1;
  cost[11][12] = 1;
  cost[12][7] = cost[12][13] = 1;
  cost[13][8] = 1;

  // Floyd-warshall
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  matrix ans = matrix(n * n, vector<ll>(n * n));
  matrix a = matrix(n * n, vector<ll>(n * n));
  for (int i = 0; i < n * n; i++) ans[i][i] = 1;

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    int state = i * n + j;

    for (int k = 0; k < n; k++) for (int l = 0; l < n; l++) {
      if (cost[i][k] == 1 && cost[j][l] == 1 && cost[k][l] >= 3 && cost[l][k] >= 3) {
        int next_state = k * n + l;
        a[state][next_state] = 1;
      }
    }
  }

  int k;
  cin >> k;

  // Exponentiation by squaring
  while (k) {
    if (k & 1) ans = ans * a;
    a = a * a;
    k /= 2;
  }

  int res = 0;
  for (int i = 0; i < n * n; i++) res = (res + ans[21][i]) % MOD;
  cout << res << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
