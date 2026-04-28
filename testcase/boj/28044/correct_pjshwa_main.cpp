#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int ban[MAXN + 1];
int dp1[MAXN + 1], dp2[MAXN + 1][MAXN + 1];

void solve() {
  int N, K, E; cin >> N >> K >> E;
  int L = E, R = N - E - K;
  ban[K] = 1;

  int ans;
  if (L == R && L == K) {
    ans = L + R; dp2[0][0] = 1;
    for (int i = 1; i <= L; ++i) {
      if (ban[i]) continue;
      for (int l = L; l >= 0; --l) for (int r = R; r >= 0; --r) {
        if (l >= i) dp2[l][r] |= dp2[l - i][r];
        if (r >= i) dp2[l][r] |= dp2[l][r - i];
      }
    }
    for (int l = 0; l <= L; ++l) for (int r = 0; r <= R; ++r) {
      if (dp2[l][r]) ans = min(ans, L + R - l - r);
    }
  } else if (L == R || R == K) {
    ban[L] = 1;
    ans = R; dp1[0] = 1;
    for (int i = 1; i <= R; ++i) {
      if (ban[i]) continue;
      for (int r = R; r >= i; --r) dp1[r] |= dp1[r - i];
    }
    for (int r = 0; r <= R; ++r) {
      if (dp1[r]) ans = min(ans, R - r);
    }
  } else if (L == K) {
    ban[R] = 1;
    ans = L; dp1[0] = 1;
    for (int i = 1; i <= L; ++i) {
      if (ban[i]) continue;
      for (int l = L; l >= i; --l) dp1[l] |= dp1[l - i];
    }
    for (int l = 0; l <= L; ++l) {
      if (dp1[l]) ans = min(ans, L - l);
    }
  } else {
    ans = 0;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
