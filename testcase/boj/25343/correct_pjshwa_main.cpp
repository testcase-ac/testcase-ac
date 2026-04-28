#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int A[MAX][MAX], d[MAX][MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> A[i][j];

  int ans = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    d[i][j] = 1;
    for (int u = 0; u <= i; u++) for (int v = 0; v <= j; v++) {
      if (A[u][v] < A[i][j]) d[i][j] = max(d[i][j], d[u][v] + 1);
    }
    ans = max(ans, d[i][j]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
