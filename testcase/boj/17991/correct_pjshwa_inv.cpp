#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  vector<int> C(2 * N - 1);
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    C[i + j] += (S[i] - '0') * (S[j] - '0');
    C[i + j] %= 10;
  }

  for (int i = 0; i < 2 * N - 1; ++i) cout << C[i];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
