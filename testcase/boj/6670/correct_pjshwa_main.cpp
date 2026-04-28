#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

pll ext_gcd(ll a, ll b) {
  if (b) {
    auto tmp = ext_gcd(b, a % b);
    return {tmp.second, tmp.first - (a / b) * tmp.second};
  } else return {1, 0};
}

ll A, B, C, k;
void solve() {
  ll M = 1LL << k;
  ll D = (B - A + M) % M;

  ll g = __gcd(C, M);
  if (D % g) return cout << "FOREVER\n", void();

  C /= g, M /= g, D /= g;
  auto [X, Y] = ext_gcd(C, M);
  if (X < 0) X += M;
  cout << (X * D) % M << '\n';
}

int main() {
  fast_io();

  while (cin >> A >> B >> C >> k) {
    if (A == 0 && B == 0 && C == 0 && k == 0) break;
    solve();
  }
}
