#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
__int128_t A[MAX], B[MAX];

bool is_square(__int128_t x) {
  __int128_t s = sqrt(x);
  return s * s == x;
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    ll x;
    cin >> x;
    A[i] = B[i] = x;
  }
  sort(B, B + N);

  for (int i = 0; i < N; i++) {
    __int128_t g = __gcd(A[i], B[i]);
    A[i] /= g;
    B[i] /= g;
    if (is_square(A[i]) && is_square(B[i])) continue;
    return cout << "NO" << '\n', void();
  }
  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
