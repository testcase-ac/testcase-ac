#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int A[MAX + 1][MAX + 1];

void solve() {
  int s, m;
  cin >> s >> m;
  while (m--) {
    int x, y;
    cin >> x >> y;
    A[x][y]++;
  }
  if (s < MAX) s++;

  for (int i = 1; i <= MAX; i++) for (int j = 1; j <= MAX; j++) {
    A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
  }

  int ans = 0;
  for (int i = s; i <= MAX; i++) for (int j = s; j <= MAX; j++) {
    int val = A[i][j] - A[i - s][j] - A[i][j - s] + A[i - s][j - s];
    ans = max(ans, val);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
