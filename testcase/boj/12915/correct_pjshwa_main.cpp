#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int E, EM, M, MH, H, ans = 0; cin >> E >> EM >> M >> MH >> H;

  // i: # of EM questions used as Easy
  for (int i = 0; i <= EM; i++) {
    int ecnt = E + i, mcnt = M + EM - i, hcnt = H;
    int rest = MH;

    // "Even out" the number of questions used as Medium and Hard
    if (mcnt > hcnt) {
      int dif = mcnt - hcnt;
      int add = min(dif, rest);
      hcnt += add; rest -= add;
    }
    if (mcnt < hcnt) {
      int dif = hcnt - mcnt;
      int add = min(dif, rest);
      mcnt += add; rest -= add;
    }

    assert(mcnt == hcnt || rest == 0);
    mcnt += rest / 2; hcnt += rest / 2;
    ans = max(ans, min({ecnt, mcnt, hcnt}));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
