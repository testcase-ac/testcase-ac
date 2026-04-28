#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, W; cin >> N >> W;

  int score = 10 * N;
  if (N >= 3) score += 20;
  if (N == 5) score += 50;
  if (W > 1000) score = max(0, score - 15);

  cout << score << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
