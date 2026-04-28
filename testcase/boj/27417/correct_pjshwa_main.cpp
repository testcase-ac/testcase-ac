#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll ask(ll x) {
  cout << "query " << x << endl;
  ll ret; cin >> ret;
  return ret;
}

void solve() {
  ll osum = ask(0), ans = 0;

  ll pre = 1;
  for (int b = 0; b < 18; b++) {
    ll m1 = ask(3 * pre), m2 = ask(7 * pre), cur;

    // Candidate is in [4, 7]
    if (m1 >= m2) {
      ll m3 = ask(5 * pre);
      if (m1 >= m3) {
        ll m4 = ask(4 * pre);
        cur = m1 >= m4 ? 4 : 5;
      }
      else {
        ll m4 = ask(6 * pre);
        cur = m3 >= m4 ? 6 : 7;
      }
    }

    // Candidate is in [1, 3]
    else if (osum >= m1) {
      ll m3 = ask(1 * pre), m4 = ask(2 * pre);
      if (osum >= m3) cur = 1;
      else if (m3 >= m4) cur = 2;
      else cur = 3;
    }

    // Candidate is in [8, 9]
    else {
      ll m3 = ask(8 * pre), m4 = ask(9 * pre);
      if (m4 > osum) cur = 0;
      else if (m3 >= m4) cur = 9;
      else cur = 8;
    }

    cur = (10 - cur) % 10;
    ans += cur * pre;
    pre *= 10;
  }

  cout << "answer " << ans << endl;
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
