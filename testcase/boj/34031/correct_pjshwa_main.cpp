#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int C[MAXN + 1];

void solve() {
  string A, B; cin >> A >> B;
  int z = 0;
  for (auto& c : A) {
    if (c == '(') z += 1;
    else z -= 1;
    if (z < 0) break;
    ++C[z];
  }

  ll t = 0, mint = 0, ans = 0;
  for (auto& c : B) {
    if (c == '(') t += 1;
    else {
      t -= 1;
      mint = min(mint, t);
      if (mint == t) ans += C[-t];
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
