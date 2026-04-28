#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll N, M;
void solve() {
  for (ll i = 2;; i++) {
    if (M == 1) {
      cout << N << '\n';
      break;
    }

    if (i * M > N) {
      ll nom = M * i - N, denom = i * N;
      ll g = __gcd(nom, denom);
      if (denom / g >= 1e6) continue;

      cout << i << ' ';
      M = nom / g, N = denom / g;
    }
  }
}

int main() {
  fast_io();

  while (cin >> M >> N) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
