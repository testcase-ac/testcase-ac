#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, X;
  cin >> N >> X;
  vector<int> T(N);
  for (int i = 0; i < N; ++i) cin >> T[i];

  int c = X, i = 0;
  while (1) {
    if (T[i] < c) return cout << i + 1 << '\n', void();

    c++;
    i = (i + 1) % N;
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
