#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int A[MAX][MAX], C[MAX][MAX];

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> A[i][j];

  for (int i = 0; i < n; i++) {
    int hmax = 0;
    for (int j = 0; j < m; j++) hmax = max(hmax, A[i][j]);
    for (int j = 0; j < m; j++) C[i][j] |= A[i][j] == hmax;
  }
  for (int j = 0; j < m; j++) {
    int hmax = 0;
    for (int i = 0; i < n; i++) hmax = max(hmax, A[i][j]);
    for (int i = 0; i < n; i++) C[i][j] |= A[i][j] == hmax;
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) ans += !C[i][j] * A[i][j];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
