#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll r(ll N) {
  if (N <= 5) return N;

  ll p = 1, o = 0;
  while (p * 5 < N) p *= 5, o ^= 1;

  ll po = 0, pv = r(p), ret = 0;
  for (int i = 0; i < N / p; i++) {
    if (po) ret += p - pv;
    else ret += pv;
    po ^= o;
  }

  if (po) return ret + (N % p) - r(N % p);
  else return ret + r(N % p);
}

ll N;
void solve() {
  cout << r(N + 1) << '\n';
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == -1) break;
    solve();
  }
}
