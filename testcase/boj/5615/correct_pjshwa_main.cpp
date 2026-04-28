#include <bits/stdc++.h>
typedef unsigned long long ull;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ull lpow(ull x, ull y, ull m){
  ull r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

inline bool miller_rabin(ull n, ull a) {
  ull d = n - 1;
  while (d % 2 == 0) {
    if (lpow(a, d, n) == n - 1) return true;
    d /= 2;
  }
  ull r = lpow(a, d, n);
  return r == n - 1 || r == 1;
}

bool is_prime(ull n) {
  if (n == 1) return false;
  for (ull a : {2, 7, 61}) {
    if (n == a) return true;
    if (!miller_rabin(n, a)) return false;
  }
  return true;
}

int main() {
  fast_io();

  int t, cnt = 0;
  ull n;
  cin >> t;
  while (t--) {
    cin >> n;
    if (is_prime(2 * n + 1)) cnt++;
  }
  cout << cnt;
}
