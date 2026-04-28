#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int A[MAX][MAX];

void solve() {
  int N, M;
  cin >> N >> M;

  int zc = 0, oc = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    cin >> A[i][j];
    if (A[i][j] == 0) zc++;
    else oc++;
  }
  if (zc & 1) return cout << "-1\n", void();
  if (oc & 1) return cout << "-1\n", void();

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

      if (A[i][j] == A[ni][nj]) return cout << "1\n", void();
    }
  }
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
