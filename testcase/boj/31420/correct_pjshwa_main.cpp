#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int B[26][26];

void solve() {
  int N, M; string T; cin >> N >> T >> M;
  while (M--) {
    string S; cin >> S;
    int u = S[0] - 'a', v = S[1] - 'a';
    B[u][v] = 1;
  }

  int req = 0;
  for (int l1 = 0; l1 < 26; ++l1) for (int l2 = 0; l2 < 26; ++l2) req += B[l1][l2];

  int r1 = 1, r2 = 1, C1[26][26]{}, C2[26][26]{};
  ll ans = 0;
  for (int i = 1; i < N; ++i) {
    if (i > 1) {
      int u = T[i - 2] - 'a', v = T[i - 1] - 'a';
      r1 >= i ? --C1[u][v] : r1 = i;
      r2 >= i ? --C2[u][v] : r2 = i;
      if (B[u][v] && C1[u][v] == 0) ++req;
    }

    while (r1 < N && req) {
      int nu = T[r1 - 1] - 'a', nv = T[r1] - 'a';
      if (B[nu][nv] && C1[nu][nv] == 0) --req;
      ++C1[nu][nv]; ++r1;
    }
    while (r2 < N) {
      int nu = T[r2 - 1] - 'a', nv = T[r2] - 'a';
      if (B[nu][nv] == 0) break;
      ++C2[nu][nv]; ++r2;
    }

    if (req == 0) ans += max(0, r2 - r1 + 1);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
