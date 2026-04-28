#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  bool f = true;
  for (int i = 0; i < N; i++) {
    cin >> B[i];
    f &= A[i] == B[i];
  }

  if (f) return cout << "POSSIBLE\n", []{}();

  bool sgn = B[0] < B[1];
  for (int i = 1; i < N - 1; i++) {
    bool sgn2 = B[i] < B[i + 1];
    if (sgn == sgn2) return cout << "POSSIBLE\n", []{}();
    sgn = sgn2;
  }
  cout << "IMPOSSIBLE\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
