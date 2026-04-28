#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;
  vector<int> A(N + 1);
  for (int i = 1; i <= N; i++) cin >> A[i];

  vector<pii> ops;
  for (int i = 1; i <= N; i++) {
    if (A[i] == i) continue;

    for (int j = i + 1; j <= N; j++) {
      if (A[j] != i) continue;

      ops.emplace_back(i, j);
      reverse(A.begin() + i, A.begin() + j + 1);
    }
  }

  cout << ops.size() << '\n';
  for (auto [a, b] : ops) cout << a << ' ' << b << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
