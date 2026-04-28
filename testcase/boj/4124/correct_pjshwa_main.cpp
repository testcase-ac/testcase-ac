#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll f1, ff1;
  cin >> f1 >> ff1;

  if (f1 < 0) cout << "IMPOSSIBLE\n";
  else if (f1 == 0) {
    if (ff1 == 0) cout << "0\n";
    else cout << "IMPOSSIBLE\n";
  }
  else if (f1 == 1) {
    if (ff1 == 1) cout << "AMBIGUOUS\n";
    else cout << "IMPOSSIBLE\n";
  }
  else {
    ll d = 1, dpw = f1;
    while (dpw * f1 < ff1) {
      dpw *= f1;
      d++;
    }

    vector<ll> ans;
    while (dpw) {
      ans.push_back(ff1 / dpw);
      ff1 %= dpw;
      dpw /= f1;
    }

    if (accumulate(ans.begin(), ans.end(), 0) == f1) {
      for (auto e : ans) cout << e << ' ';
      cout << '\n';
    }
    else cout << "IMPOSSIBLE\n";
  }

}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
