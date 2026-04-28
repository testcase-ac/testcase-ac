#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
char board1[MAXN + 1][MAXN + 1];
char board2[MAXN + 1][MAXN + 1];
int A[MAXN + 1][MAXN + 1];

void solve() {
  int N; cin >> N;
  if (N > 2) return cout << "0\n", void();

  for (int i = 0; i < N; ++i) cin >> board1[i];
  for (int i = 0; i < N; ++i) {
    cin >> board2[i];
    for (int j = 0; j < N; ++j) {
      A[i][j] = (board2[i][j] - board1[i][j] + 4) % 4;
    }
  }

  int ans = 1000;
  for (int k1 = 0; k1 < 4; ++k1) for (int k2 = 0; k2 < 4; ++k2) 
  for (int k3 = 0; k3 < 4; ++k3) for (int k4 = 0; k4 < 4; ++k4) {
    int x1 = (k1 + k2 + k3) % 4;
    int x2 = (k1 + k2 + k4) % 4;
    int x3 = (k1 + k3 + k4) % 4;
    int x4 = (k2 + k3 + k4) % 4;

    if (A[0][0] == x1 && A[0][1] == x2 && A[1][0] == x3 && A[1][1] == x4) {
      ans = min(ans, k1 + k2 + k3 + k4);
    }
  }

  if (ans == 1000) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
