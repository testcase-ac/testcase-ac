#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; string S; cin >> N >> S >> K;

  for (int t = K - 1; t <= K + 1; ++t) {
    if (t < 1 || t > N) continue;

    bool fit = (S == "induck") ^ (t % 2 == 1);
    if (!fit) continue;

    return cout << t << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
