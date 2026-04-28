#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e6;
int C[MAXV + 1], T[MAXV + 1];

void solve() {
  int N, K; cin >> N >> K;
  vector<int> A(N);
  for (auto& x : A) cin >> x, ++C[x];

  for (int d = K + 1; d <= MAXV; ++d) {
    if (C[d] == 0) continue;
    for (int i = K; i <= MAXV; i += d) T[i] += C[d];
  }
  for (auto& x : A) cout << T[x] - (K == 0) << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
