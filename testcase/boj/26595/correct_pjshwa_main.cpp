#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, A, Pa, B, Pb; cin >> N >> A >> Pa >> B >> Pb;

  ll ans = 0, px = 0, py = 0;
  for (int x = 0;; x++) {
    ll acost = Pa * x;
    if (acost > N) break;

    ll y = (N - acost) / Pb;
    ll val = A * x + B * y;
    if (val > ans) ans = val, px = x, py = y;
  }
  cout << px << " " << py << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
