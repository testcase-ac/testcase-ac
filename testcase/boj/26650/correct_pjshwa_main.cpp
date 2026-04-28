#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 26;
ll d[MAXV];

void solve() {
  string S;
  cin >> S;
  int N = S.size();

  int as = 0, cc = 0;
  ll ans = 0;
  for (int i = 0; i < N; i++) {
    if (S[i] == 'A') {
      if (cc != 1) cc = 1, as = 0;
      as++;
    }
    else if (S[i] == 'Z') {
      if (cc >= 25) {
        cc = 26;
        ans += as;
      }
      else cc = 0;
    }
    else {
      int nc = S[i] - 'A' + 1;
      if (nc == cc || nc == cc + 1) cc = nc;
      else cc = 0;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
