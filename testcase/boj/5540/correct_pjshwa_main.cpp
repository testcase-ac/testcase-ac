#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3000;
int A[MAX + 1], B[MAX + 1];
int dl[MAX + 5][MAX + 5], dr[MAX + 5][MAX + 5];

void solve() {
  int N, T, S;
  cin >> N >> T >> S;
  for (int i = 1; i <= N; i++) cin >> A[i] >> B[i];

  for (int i = 1; i <= N; i++) {
    for (int j = 0; j <= MAX; j++) dl[i][j] = dl[i - 1][j];
    for (int j = 0; j <= MAX; j++) {
      if (j < B[i]) continue;
      dl[i][j] = max(dl[i][j], dl[i - 1][j - B[i]] + A[i]);
    }
  }

  for (int i = N; i >= 1; i--) {
    for (int j = 0; j <= MAX; j++) dr[i][j] = dr[i + 1][j];
    for (int j = 0; j <= MAX; j++) {
      if (j < B[i]) continue;
      dr[i][j] = max(dr[i][j], dr[i + 1][j - B[i]] + A[i]);
    }
  }

  int ans = 0;
  for (int i = 0; i <= N; i++) {
    // cout << "i = " << i << ", dl[i][S] + dr[i + 1][T - S] = " << dl[i][S] + dr[i + 1][T - S] << endl;
    ans = max(ans, dl[i][S] + dr[i + 1][T - S]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
