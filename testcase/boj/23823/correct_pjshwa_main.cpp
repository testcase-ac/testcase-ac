#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int hmax, wmax;
int ch[MAX + 1], cw[MAX + 1], th[MAX + 1], tw[MAX + 1];

void solve() {
  int n, q;
  cin >> n >> q;
  th[0] = tw[0] = n;

  while (q--) {
    int t, a;
    cin >> t >> a;
    if (t == 1) {
      th[ch[a]]--;
      ch[a]++;
      th[ch[a]]++;
      hmax = max(hmax, ch[a]);
    }
    if (t == 2) {
      tw[cw[a]]--;
      cw[a]++;
      tw[cw[a]]++;
      wmax = max(wmax, cw[a]);
    }
    cout << th[hmax] * tw[wmax] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
