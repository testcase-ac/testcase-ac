#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A[3], B[3];
  for (int i = 0; i < 3; i++) cin >> A[i];
  for (int i = 0; i < 3; i++) cin >> B[i];

  int As = A[0] * 3 + A[1] * 2 + A[2];
  int Bs = B[0] * 3 + B[1] * 2 + B[2];
  if (As < Bs) cout << "B\n";
  else if (As > Bs) cout << "A\n";
  else cout << "T\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
