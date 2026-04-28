#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, K; cin >> N >> M >> K;
  vector<vector<int>> A(N, vector<int>(M));
  for (int i = 0; i < N; i++) {
    iota(A[i].begin(), A[i].end(), i + 1);
  }

  if (A[N - 1][M - 1] <= K) {
    cout << "YES\n";
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) cout << A[i][j] << ' ';
      cout << '\n';
    }
  }
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
