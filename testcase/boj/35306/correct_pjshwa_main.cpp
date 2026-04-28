#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000;
int P[MAXN][MAXN], S[MAXN], U[MAXN];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; ++i) for (int j = 0; j < K; ++j) {
    cin >> P[i][j];
    S[j] = max(S[j], P[i][j]);
  }
  for (int j = 0; j < K; ++j) for (int i = 0; i < N; ++i) if (P[i][j] == S[j]) ++U[j];

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    int ok = 0;
    for (int j = 0; j < K; ++j) if (P[i][j] == S[j] && U[j] == 1) ok = 1;
    ans += ok;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
