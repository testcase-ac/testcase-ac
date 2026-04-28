#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN][MAXN];

void solve() {
  int N, M, D; cin >> N >> M >> D;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) cin >> A[i][j], A[i][j] += D * i;
    sort(A[i], A[i] + M);
  }

  for (int i = 1; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (A[i][j] <= A[i - 1][j]) return cout << "NO\n", void();
  }
  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
