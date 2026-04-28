#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll nC2(ll n) {
  return n * (n - 1) / 2;
}

void solve() {
  ll L, K; cin >> L >> K;

  int bias = 0;
  for (ll N = L; N >= 1; N--) {
    if (K > nC2(N - 1)) {
      cout << N + bias << ' ';
      K -= (N - 1);
    }
    else {
      cout << 1 + bias << ' ';
      bias++;
    }
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
