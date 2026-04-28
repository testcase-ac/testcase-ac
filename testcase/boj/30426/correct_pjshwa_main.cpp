#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
bool dp[MAX + 1][MAX], sink[MAX + 1];

void solve() {
  int N, M, K; cin >> N >> M >> K;

  vector<pair<int, int>> D;
  for (int i = 0; i < K; ++i) {
    int G, Y; cin >> G >> Y;
    D.emplace_back(G, Y);
  }

  int L; cin >> L;
  while (L--) {
    int x; cin >> x;
    sink[x] = true;
  }

  dp[0][M] = true;
  for (int k = 1; k <= K; ++k) {
    auto [G, Y] = D[k - 1];
    for (int d = 0; d < N; ++d) {
      if (sink[d]) continue;
      int gd = (d + G) % N, yd = (d + Y) % N;
      dp[k][gd] |= dp[k - 1][d];
      dp[k][yd] |= dp[k - 1][d];
    }
  }

  if (dp[K][0]) cout << "utopia\n";
  else cout << "dystopia\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
