#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, A, B; cin >> N >> A >> B;
  int C = 1, D = 1;
  for (int i = 0; i < N; ++i) {
    C += A; D += B;
    if (C == D) --D;
    else if (C < D) swap(C, D);
  }
  cout << C << ' ' << D << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
