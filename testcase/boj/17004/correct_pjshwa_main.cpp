#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXS = 1e5;

// smallest index of char after i
int nxtchar[MAXS + 1][26];

void solve() {
  string S, T; cin >> S >> T;
  int Sz = S.size(), Tz = T.size();

  memset(nxtchar, -1, sizeof(nxtchar));
  for (int i = Sz - 1; i >= 0; --i) {
    for (int j = 0; j < 26; ++j) {
      nxtchar[i][j] = nxtchar[i + 1][j];
    }
    nxtchar[i][S[i] - 'a'] = i;
  }

  ll ans = 0;
  for (int i = 0; i < Sz; ++i) {
    int r = i;
    for (int j = 0; j < Tz; ++j) {
      r = nxtchar[r][T[j] - 'a'];
      if (r == -1) break;
      ++r;
    }
    if (r != -1) ans += (Sz - r + 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
