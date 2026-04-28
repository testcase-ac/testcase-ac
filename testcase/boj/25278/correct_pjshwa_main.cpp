#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int q;
  cin >> q;

  int oxy = 0, oce = 0, tem = -30;
  while (q--) {
    string s; int v;
    cin >> s >> v;

    if (s == "temperature") tem += v;
    if (s == "oxygen") oxy += v;
    if (s == "ocean") oce += v;
  }

  if (oce >= 9 && oxy >= 14 && tem >= 8) cout << "liveable\n";
  else cout << "not liveable\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
