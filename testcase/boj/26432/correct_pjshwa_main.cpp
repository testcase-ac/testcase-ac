#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int A[1001][32];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int M, N, P; cin >> M >> N >> P;
  for (int i = 1; i <= M; i++) for (int j = 1; j <= N; j++) cin >> A[i][j];

  int ans = 0;
  for (int j = 1; j <= N; j++) {
    int cur = 0, val = A[P][j];
    for (int i = 1; i <= M; i++) {
      if (i == P) continue;
      cur = max(cur, A[i][j] - val);
    }
    ans += cur;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
