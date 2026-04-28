#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void solve() {
  int N, M, A, H;
  cin >> N >> M >> A >> H;
  cout << lpow(M, N - 1, MOD) << '\n';

  // int A = 7, M = 55;
  // cin >> A >> M;
  // int C[M] = {0};
  // for (int i = 0; i < M; i++) {
  //   for (int j = 0; j < M; j++) {
  //     for (int k = 0; k < M; k++) {
  //       int v = i + A * j + (A * A) * k;
  //       C[v % M]++;
  //     }
  //   }
  // }

  // for (int i = 0; i < M; i++) {
  //   cout << "C[" << i << "] = " << C[i] << '\n';
  // }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
