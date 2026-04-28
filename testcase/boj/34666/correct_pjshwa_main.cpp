#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int G, K, R, L; cin >> G >> K >> R >> L;
  if (G >= 3) return cout << "NO\n", void();
  if (L < 50) return cout << "NO\n", void();

  int con1 = 0, con2 = 0, LIM = G == 1 ? 100 : 90;
  if (K * 3 < LIM) ++con1;
  if (R * 3 < LIM) ++con1;
  if (K <= 21) ++con2;
  if (R <= 21) ++con2;

  if (con1 >= 2 || con2 >= 1) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
