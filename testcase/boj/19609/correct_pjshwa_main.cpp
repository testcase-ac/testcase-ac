#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e6;
int Pa[MAXN + 1], Pb[MAXN + 1], Pc[MAXN + 1];

void solve() {
  string S; cin >> S;

  int N = S.size(), ac = 0, bc = 0, cc = 0;
  for (int i = 0; i < 2 * N; ++i) {
    char c = S[i % N];
    Pa[i + 1] = Pa[i]; Pb[i + 1] = Pb[i]; Pc[i + 1] = Pc[i];
    if (c == 'A') ++ac, ++Pa[i + 1];
    if (c == 'B') ++bc, ++Pb[i + 1];
    if (c == 'C') ++cc, ++Pc[i + 1];
  }
  ac /= 2, bc /= 2, cc /= 2;

  int ans = N;

  // 'B' followed by 'A'
  for (int s = 0; s < N; ++s) {
    int bs = s, be = s + bc;
    int as = be, ae = as + ac;

    int tot = ac - (Pa[ae] - Pa[as]) + bc - (Pb[be] - Pb[bs]);
    tot -= min(Pa[be] - Pa[bs], Pb[ae] - Pb[as]);

    ans = min(ans, tot);
  }

  // 'C' followed by 'A'
  for (int s = 0; s < N; ++s) {
    int cs = s, ce = s + cc;
    int as = ce, ae = as + ac;

    int tot = ac - (Pa[ae] - Pa[as]) + cc - (Pc[ce] - Pc[cs]);
    tot -= min(Pa[ce] - Pa[cs], Pc[ae] - Pc[as]);

    ans = min(ans, tot);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
