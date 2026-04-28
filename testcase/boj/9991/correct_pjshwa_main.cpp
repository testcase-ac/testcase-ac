#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int w, q;
  cin >> w >> q;
  vector<string> wa(w);
  map<string, int> winv;
  for (int i = 0; i < w; ++i) cin >> wa[i], winv[wa[i]] = i + 1;
  sort(wa.begin(), wa.end());

  while (q--) {
    int ki;
    string pw;
    cin >> ki >> pw;

    int lt = lower_bound(wa.begin(), wa.end(), pw) - wa.begin();
    pw[pw.size() - 1]++;
    int gt = lower_bound(wa.begin(), wa.end(), pw) - wa.begin();

    if (ki > gt - lt) cout << -1 << '\n';
    else cout << winv[wa[lt + ki - 1]] << '\n';
  }
}
