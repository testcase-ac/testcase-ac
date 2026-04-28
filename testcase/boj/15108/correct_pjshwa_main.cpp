#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; ld X, v; cin >> n >> X >> v;

  ld dsum = 0;
  for (int i = 0; i < n; ++i) {
    int li, ri; ld vi; cin >> li >> ri >> vi;
    dsum += vi * (ri - li);
  }
  dsum = abs(dsum);
  if (dsum > X * v) {
    cout << "Too hard\n";
    return;
  }

  ld sinth = dsum / (v * X);
  ld costh = sqrt(1 - sinth * sinth);
  ld Y = X / costh;

  ld ans = Y / v;
  cout << fixed << setprecision(3) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
