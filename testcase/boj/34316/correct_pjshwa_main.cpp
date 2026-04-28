#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;
  vector<vector<int>> A(N, vector<int>(M, 0));
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> A[i][j];

  vector<int> C(20); ll ans = 0;
  if (N < M) {
    for (int i1 = 0; i1 < N; ++i1) for (int i2 = i1 + 1; i2 < N; ++i2) {
      fill(C.begin(), C.end(), 0);
      for (int j = 0; j < M; ++j) {
        int sum = A[i1][j] + A[i2][j];
        ans += C[20 - sum];
        ++C[sum];
      }
    }
  } else {
    for (int j1 = 0; j1 < M; ++j1) for (int j2 = j1 + 1; j2 < M; ++j2) {
      fill(C.begin(), C.end(), 0);
      for (int i = 0; i < N; ++i) {
        int sum = A[i][j1] + A[i][j2];
        ans += C[20 - sum];
        ++C[sum];
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
