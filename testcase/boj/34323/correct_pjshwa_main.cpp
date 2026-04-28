#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, M, S; cin >> N >> M >> S;

  ll pA = S * (M + 1) * (100 - N);
  ll pB = S * M * 100;
  cout << min(pA, pB) / 100 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
