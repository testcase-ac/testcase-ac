#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll N;
ll xshuf(ll x) {
  return 2 * x % N;
}

ll yshuf(ll x) {
  return (2 * x + 1) % N;
}

void solve() {
  ll A, B; cin >> N >> A >> B; --A; --B;
  ll L = A, U = A, Bm = A > B ? B + N : B;

  for (int t = 0;; ++t) {
    if (L <= Bm && Bm <= U) {
      ll w = Bm - L;
      for (int b = t - 1; b >= 0; --b) {
        if (w & (1LL << b)) cout << 'Y';
        else cout << 'X';
      }
      break;
    }
    L = 2 * L;
    U = 2 * U + 1;
    Bm = L + (B - (L % N) + N) % N;
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
