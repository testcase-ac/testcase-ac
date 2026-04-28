#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
bool C[MAX + 1][MAX + 1], O[MAX + 1][MAX + 1];;
int cnt, ocnt;

void copy() {
  for (int i = 1; i <= MAX; i++) {
    for (int j = 1; j <= MAX; j++) {
      C[i][j] = O[i][j];
    }
  }
  cnt = ocnt;
}

void solve() {
  int N, M;
  cin >> N >> M;
  while (M--) {
    int u, v;
    cin >> u >> v;
    O[u][v] = O[v][u] = true;
    ocnt += 2;
  }

  copy();
  for (int i = 2; i <= N; i++) {
    if (C[1][i]) continue;

    for (int j = 1; j <= N; j++) {
      if (i == j) continue;
      C[i][j] ^= 1;
      C[j][i] ^= 1;
      cnt += C[i][j] ? 2 : -2;
    }
  }
  if (cnt == N * (N - 1)) return cout << "DA\n", void();

  copy();
  for (int j = 2; j <= N; j++) {
    C[1][j] ^= 1;
    C[j][1] ^= 1;
    cnt += C[1][j] ? 2 : -2;
  }
  for (int i = 2; i <= N; i++) {
    if (C[1][i]) continue;

    for (int j = 1; j <= N; j++) {
      if (i == j) continue;
      C[i][j] ^= 1;
      C[j][i] ^= 1;
      cnt += C[i][j] ? 2 : -2;
    }
  }
  if (cnt == N * (N - 1)) return cout << "DA\n", void();

  cout << "NE\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
