#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4;
bool R[26];

void solve() {
  int N, K, Q;
  cin >> N >> K >> Q;

  vector<pii> A(K + 1);
  for (int i = 1; i <= K; i++) {
    int O; string U;
    cin >> O >> U;
    A[i] = {O, U[0] - 'A'};
  }

  int L = A[Q].first;
  if (L == 0) return cout << "-1\n", void();

  for (int i = 1; i <= K; i++) {
    auto [O, U] = A[i];
    if (O >= L) R[U] = true;
  }
  R[0] = true;

  for (int i = 0; i < N; i++) {
    if (!R[i]) cout << (char)('A' + i) << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
