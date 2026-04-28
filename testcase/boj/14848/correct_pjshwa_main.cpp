#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 15;
int A[MAX];

__int128_t lcm(__int128_t a, __int128_t b) {
  return a * b / __gcd(a, b);
}

void solve() {
  int N, K;
  cin >> N >> K;
  for (int i = 0; i < K; i++) cin >> A[i];

  int ans = N;
  for (int state = 1; state < (1 << K); state++) {
    bool f = __builtin_popcount(state) & 1;
    
    __int128_t l = 1;
    for (int i = 0; i < K; i++) {
      if (state & (1 << i)) l = lcm(l, A[i]);
    }

    auto d = N / l;
    if (f) d = -d;
    ans += d;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
