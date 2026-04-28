#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN + 5][MAXN + 5], P[MAXN + 5][MAXN + 5];

void solve() {
  int N, Q; cin >> N >> Q;
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) cin >> A[i][j];

  while (Q--) {
    int r1, c1, r2, c2, v; cin >> r1 >> c1 >> r2 >> c2 >> v;
    P[r1][c1] += v;
    P[r1][c2 + 1] -= v;
    P[r2 + 1][c1] -= v;
    P[r2 + 1][c2 + 1] += v;
  }

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= N; ++j) {
      P[i][j] += P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1];
      A[i][j] += P[i][j];
      cout << A[i][j] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
