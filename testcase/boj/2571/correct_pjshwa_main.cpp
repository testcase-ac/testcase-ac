#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 100;
int A[MAX + 1][MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    for (int i = x + 1; i <= x + 10; i++) for (int j = y + 1; j <= y + 10; j++) A[i][j] = 1;
  }

  for (int i = 1; i <= MAX; i++) for (int j = 1; j <= MAX; j++) {
    A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
  }

  int ans = 0;
  for (int x1 = 1; x1 <= MAX; x1++) for (int x2 = x1; x2 <= MAX; x2++)
  for (int y1 = 1; y1 <= MAX; y1++) for (int y2 = y1; y2 <= MAX; y2++) {
    int cnt = A[x2][y2] - A[x1 - 1][y2] - A[x2][y1 - 1] + A[x1 - 1][y1 - 1];
    int area = (x2 - x1 + 1) * (y2 - y1 + 1);
    if (cnt == area) ans = max(ans, area);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
