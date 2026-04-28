#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[(int)1e6];
int pf[(int)1e6];
int main() {
  fast_io();

  map<int, int> occ;
  int tt, n, m;
  cin >> tt;

  while (tt--) {
    occ.clear();
    cin >> m >> n;

    for (int i = 0; i < n; i++) cin >> a[i];

    pf[0] = a[0] % m;
    for (int i = 1; i < n; i++) pf[i] = (pf[i - 1] + a[i]) % m;

    for (int i = 0; i < n; i++) {
      auto found = occ.find(pf[i]);
      if (found != occ.end()) found->second++;
      else occ.insert({pf[i], 1});
    }

    long long ans = 0, key, val;
    for (auto iter = occ.begin(); iter != occ.end(); iter++) {
      key = iter->first;
      val = iter->second;
      if (key == 0) ans += (val * val + val) / 2;
      else ans += (val * val - val) / 2;
    }

    cout << ans << '\n';
  }
}
