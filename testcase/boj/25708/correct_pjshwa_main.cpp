#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int A[MAX + 1][MAX + 1];
int R[MAX + 1], C[MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> A[i][j];

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) R[i] += A[i][j];
  }
  for (int j = 1; j <= M; j++) {
    for (int i = 1; i <= N; i++) C[j] += A[i][j];
  }

  int ans = -0x3f3f3f3f;
  for (int i1 = 1; i1 <= N; i1++) for (int i2 = i1 + 1; i2 <= N; i2++)
  for (int j1 = 1; j1 <= M; j1++) for (int j2 = j1 + 1; j2 <= M; j2++) {
    int cur = R[i1] + R[i2] + C[j1] + C[j2];
    cur -= (A[i1][j1] + A[i1][j2] + A[i2][j1] + A[i2][j2]);

    int h = i2 - i1 - 1, w = j2 - j1 - 1;
    ans = max(ans, cur + h * w);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
