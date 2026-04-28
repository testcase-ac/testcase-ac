#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN][MAXN];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> A[i][j], A[i][j] /= 100;

  int ans = 1, target = 0;
  for (int j = 0; j < M; ++j) target += A[0][j];
  for (int i = 1; i < N; ++i) {
    int cnt = 0;
    for (int j = 0; j < M; ++j) cnt += (A[0][j] & A[i][j]);
    if (cnt == target) ++ans;
  }
  cout << "1 " << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
