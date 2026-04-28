#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;
  if (N == 1 && K == 2) return cout << "-1\n", void();

  if (K <= 1) {
    for (int i = 0; i < N; ++i) cout << K << ' ';
  } else if (K == 2) {
    cout << "0 ";
    for (int i = 1; i < N; ++i) cout << "2 ";
  } else {
    for (int i = 0; i < K - 2; ++i) cout << i << ' ';
    for (int i = K - 2; i < N; ++i) cout << K - 2 << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
