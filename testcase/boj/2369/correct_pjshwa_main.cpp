#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 256;
int A[MAX + 1][MAX + 1];

void solve() {
  int N, M, K;
  cin >> N >> M >> K;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> A[i][j];
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
    A[i][j] = A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1] + A[i][j];
  }

  int ans = 0;
  for (int i1 = 0; i1 < N; i1++) for (int i2 = i1 + 1; i2 <= N; i2++) {
    map<int, int> d;
    d[0] = 1;

    int cur = 0;
    for (int j = 1; j <= M; j++) {
      cur = (cur + A[i2][j] - A[i1][j] - A[i2][j - 1] + A[i1][j - 1]) % K;
      ans += d[cur];
      d[cur]++;
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
