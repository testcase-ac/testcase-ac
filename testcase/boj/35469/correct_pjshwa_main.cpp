#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN][MAXN];

void solve() {
  int N, K; cin >> N >> K;
  if (K == 1) return cout << "LOSE\n", void();

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> A[i][j];
  for (int j = 0; j < N; j += K) {
    for (int i = 0; i < N; ++i) --A[i][j];

    int l = j + K - 1;
    if (l < N) {
      for (int i = 0; i < N; ++i) ++A[i][l];
    }
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cout << A[i][j] << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
