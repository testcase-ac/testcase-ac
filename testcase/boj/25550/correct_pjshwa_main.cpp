#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int A[MAX + 10][MAX + 10];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> A[i][j];

  ll ans = 0;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
    if (A[i][j] == 0) continue;

    int cur = A[i][j] - 1;
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      cur = min(cur, A[ni][nj]);
    }
    ans += cur;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
