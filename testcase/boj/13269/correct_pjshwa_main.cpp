#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
int A[MAXN][MAXN], U[MAXN][MAXN];
int F[MAXN], R[MAXN];

void error() {
  cout << "-1\n";
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    cin >> U[i][j];
    A[i][j] = U[i][j] * 101;
  }
  for (int j = 0; j < M; ++j) {
    cin >> F[j];
    for (int i = 0; i < N; ++i) A[i][j] = min(A[i][j], F[j]);
  }
  for (int i = N - 1; i >= 0; --i) {
    cin >> R[i];
    for (int j = 0; j < M; ++j) A[i][j] = min(A[i][j], R[i]);
  }

  // validation
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (U[i][j] == 1 && A[i][j] == 0) return error();
  }
  for (int j = 0; j < M; ++j) {
    int val = 0;
    for (int i = 0; i < N; ++i) val = max(val, A[i][j]);
    if (val != F[j]) return error();
  }
  for (int i = 0; i < N; ++i) {
    int val = 0;
    for (int j = 0; j < M; ++j) val = max(val, A[i][j]);
    if (val != R[i]) return error();
  }

  // no error, print ans
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) cout << A[i][j] << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
