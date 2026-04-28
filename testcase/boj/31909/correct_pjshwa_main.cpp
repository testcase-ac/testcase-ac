#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

pii C[256];
int P[8];

void solve() {
  int N; cin >> N;

  vector<int> O(N);
  for (int i = 0; i < N; ++i) cin >> O[i];

  iota(P, P + 8, 0);
  for (int s : O) {
    if (C[s].first == -1) continue;
    auto [i, j] = C[s];
    swap(P[i], P[j]);
  }

  int K; cin >> K;
  cout << P[K] << '\n';
}

int main() {
  fast_io();

  fill(C, C + 256, pii(-1, -1));
  for (int i = 0; i < 8; ++i) for (int j = i + 1; j < 8; ++j) {
    int s = (1 << i) + (1 << j);
    C[s] = {i, j};
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
