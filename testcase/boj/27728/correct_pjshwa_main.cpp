#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500, INF = 0x3f3f3f3f;
int A[MAX + 10][MAX + 10], B[MAX + 10][MAX + 10];

void solve() {
  int N, Q; cin >> N >> Q;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) cin >> A[i][j];
    for (int j = N; j >= 1; j--) B[i][j] = B[i][j + 1] + A[i][j];
  }

  for (int j = 1; j <= N; j++) {
    for (int i = 2; i <= N; i++) B[i][j] = min(B[i][j], B[i - 1][j]);
  }

  while (Q--) {
    int X, Y, L; cin >> X >> Y >> L;
    int ans = INF, acc = 0;
    for (int j = Y; j <= N; j++) {
      ans = min(ans, B[X - L][j] + acc);
      acc += A[X][j];
    }
    ans = min(ans, acc);
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
