#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 300, INF = 0x3f3f3f3f;
int P[MAX + 10][MAX + 10];

void solve() {
  int N, M, a, b, c; cin >> N >> M >> a >> b >> c;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
    cin >> P[i][j];
    P[i][j] += P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1];
  }

  // (i, j) is the starting point
  int ans = INF;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
    if (i + a - 1 <= N && b + c + j - 1 <= M) {
      int area = P[i + a - 1][b + c + j - 1] - P[i - 1][b + c + j - 1] - P[i + a - 1][j - 1] + P[i - 1][j - 1];
      ans = min(ans, area);
    }
    if (i + a + b - 1 <= N && j + a + c - 1 <= M) {
      int area = P[i + a - 1][j + c - 1] - P[i - 1][j + c - 1] - P[i + a - 1][j - 1] + P[i - 1][j - 1];
      area += P[i + a + b - 1][j + a + c - 1] - P[i + a - 1][j + a + c - 1] - P[i + a + b - 1][j + c - 1] + P[i + a - 1][j + c - 1];
      ans = min(ans, area);
    }
    if (i + a + c - 1 <= N && j + a + b - 1 <= M) {
      int area = P[i + a - 1][j + b - 1] - P[i - 1][j + b - 1] - P[i + a - 1][j - 1] + P[i - 1][j - 1];
      area += P[i + a + c - 1][j + a + b - 1] - P[i + a - 1][j + a + b - 1] - P[i + a + c - 1][j + b - 1] + P[i + a - 1][j + b - 1];
      ans = min(ans, area);
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
