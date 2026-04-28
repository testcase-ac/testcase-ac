#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int L, T, N; cin >> L >> T >> N;

  T %= (2 * L); int O = 0;
  if (T >= L) O = 1, T %= L;

  auto move = [&](int x, int d) {
    if (d == 1) {
      if (x + T <= L) return x + T;
      return 2 * L - x - T;
    }
    else {
      if (x - T >= 0) return x - T;
      return T - x;
    }
  };

  vector<int> A;
  for (int i = 0; i < N; i++) {
    int x; string ds; cin >> x >> ds;
    int d = ds == "L" ? 0 : 1;
    if (O) d ^= 1, x = L - x;
    A.push_back(move(x, d));
  }

  sort(A.begin(), A.end());
  for (int i = 0; i < N; i++) cout << A[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
