#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_adjacent(int a, int b) {
  if (abs(a - b) == 3) return true;
  if (a / 3 == b / 3 && abs(a - b) == 1) return true;
  return false;
}

void solve() {
  int P[9], K; cin >> K; --K;
  iota(P, P + 9, 0);

  int ans = 0;
  do {
    if (P[0] != K) continue;
    int ok = 1;
    for (int i = 1; i < 9; i++) {
      if (!is_adjacent(P[i - 1], P[i])) ok = 0;
    }
    ans += ok;
  } while (next_permutation(P, P + 9));
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
