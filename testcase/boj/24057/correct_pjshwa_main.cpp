#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll aa, ab, ac, ad, ba, bb, bc, bd;
  cin >> aa >> ab >> ac >> ad >> ba >> bb >> bc >> bd;

  ll g, ca, cb, cc, cd = bd;

  ca = aa * ba, cb = ab * ba + aa * bb, cc = ac * ba + aa * bc;
  g = abs(__gcd(ca, __gcd(cb, cc))) * (abs(ca) / ca);
  if (cc == 0) cout << ca / g << ' ' << cb / g << " 0 0\n";
  else cout << ca / g << ' ' << cb / g << ' ' << cc / g << ' ' << cd << '\n';

  ca = aa * ba, cb = ab * ba - aa * bb, cc = ac * ba - aa * bc;
  g = abs(__gcd(ca, __gcd(cb, cc))) * (abs(ca) / ca);
  if (cc == 0) cout << ca / g << ' ' << cb / g << " 0 0\n";
  else cout << ca / g << ' ' << cb / g << ' ' << cc / g << ' ' << cd << '\n';

  ca = aa * ba, cb = ab * bb + ac * bc * cd, cc = ac * bb + ab * bc;
  g = abs(__gcd(ca, __gcd(cb, cc))) * (abs(ca) / ca);
  if (cc == 0) cout << ca / g << ' ' << cb / g << " 0 0\n";
  else cout << ca / g << ' ' << cb / g << ' ' << cc / g << ' ' << cd << '\n';

  ca = aa * (bb * bb - bc * bc * cd), cb = ba * (ab * bb - ac * bc * cd), cc = ba * (ac * bb - ab * bc);
  g = abs(__gcd(ca, __gcd(cb, cc))) * (abs(ca) / ca);
  if (cc == 0) cout << ca / g << ' ' << cb / g << " 0 0\n";
  else cout << ca / g << ' ' << cb / g << ' ' << cc / g << ' ' << cd << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
