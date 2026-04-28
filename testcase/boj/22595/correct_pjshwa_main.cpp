#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
int A[MAXN][MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> A[i][j];

  ll ans = 0;
  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    ans += min(A[i][j], A[j][i]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
