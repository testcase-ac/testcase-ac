#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  // always make choose 2, cause overflow
  if (K < 2 * N) cout << "-1\n";

  // don't let player choose 3
  if (K > 2 * N) cout << 2 * N << '\n';

  // if player chooses 3, opponent can cause overflow, so player won't choose 3
  // so make him choose 1 the first time
  if (K == 2 * N) cout << 2 * N - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
