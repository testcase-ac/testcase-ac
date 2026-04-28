#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000, INF = 0x3f3f3f3f;
int A[MAX + 1], d[MAX + 1][MAX + 1];

void solve() {
  int N, K;
  cin >> N >> K;
  for (int i = 1; i <= N; i++) cin >> A[i];

  for (int i = 0; i <= N; i++) {
    fill(d[i], d[i] + N + 1, -INF);
  }
  d[0][0] = 0;

  for (int i = 1; i <= N; i++) {
    for (int k = 0; k <= K; k++) d[i][k] = d[i - 1][k];
    for (int k = 0; k < min(i, K); k++) {
      int score = A[i] - k;
      d[i][k + 1] = max(d[i][k + 1], d[i - 1][k] + score);
    }
  }

  cout << d[N][K] << '\n';  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
