#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 2e6, LIM = 1e18;
map<ll, string> C;

__int128_t lcm(__int128_t a, __int128_t b) {
  return a / __gcd(a, b) * b;
}

void solve() {
  ll M;
  cin >> M;
  if (C.count(M)) cout << C[M] << '\n';
  else {
    ll q = sqrt(M);
    for (ll i = q - 3; i <= q + 3; i++) {
      if (q * q + q == M) {
        cout << q << ' ' << q + 1 << '\n';
        return;
      }
    }

    cout << "NIE\n";
  }
}

int main() {
  fast_io();

  for (int L = MAX; L >= 1; L--) {
    __int128_t u = L;
    map<ll, int> P;

    for (int i = L + 1;; i++) {
      u = lcm(u, i);
      if (u > LIM) break;

      if (!P.count(u)) P[u] = i;
    }

    for (auto [u, i] : P) {
      C[u] = to_string(L) + ' ' + to_string(i);
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
