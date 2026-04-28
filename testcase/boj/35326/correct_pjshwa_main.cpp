#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll A, B, cA, cB, fA; cin >> A >> B >> cA >> cB >> fA;

  ll wantA = fA - A;
  if (wantA <= 0) return cout << "0\n", void();
  ll wantB = (wantA + cA - 1) / cA * cB - B;
  if (wantB <= 0) return cout << "0\n", void();

  cout << "wantA: " << wantA << ", wantB: " << wantB << '\n';

  ll ans = max(wantA, wantB);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
