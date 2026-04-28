#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M;
  cin >> N >> M;
  vector<vector<int>> A(N, vector<int>(M));
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> A[i][j];

  int cnt = 0;
  for (int i = 1; i < N; i++) {
    int diff = 0;
    for (int j = 0; j < M; j++) diff += abs(A[0][j] - A[i][j]);
    if (diff > 2000) cnt++;
  }

  if (cnt >= N / 2) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
