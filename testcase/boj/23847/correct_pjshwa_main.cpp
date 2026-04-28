#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  int ii = 0, in = 0, iu = 0, nn = 0, nu = 0, uu = 0;
  int inc = 0, iuc = 0, nuc = 0;
  for (int i = 0; i < n; i++) {
    string ut;
    int o;
    cin >> ut >> o;
    if (ut == "II") ii += o;
    if (ut == "IN" || ut == "NI") in += o, inc++;
    if (ut == "IU" || ut == "UI") iu += o, iuc++;
    if (ut == "NN") nn += o;
    if (ut == "NU" || ut == "UN") nu += o, nuc++;
    if (ut == "UU") uu += o;
  }

  int ans;
  if (inc == 0 && iuc == 0 && nuc == 0) {
    ans = max({ii, nn, uu});
  }
  else if (inc && iuc == 0 && nuc == 0) {
    ans = max({ii + in + nn, uu});
  }
  else if (inc == 0 && iuc && nuc == 0) {
    ans = max({ii + iu + uu, nn});
  }
  else if (inc == 0 && iuc == 0 && nuc) {
    ans = max({nn + nu + uu, ii});
  }
  else ans = ii + in + nn + nu + uu + iu;

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
