#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B, C; cin >> A >> B >> C;

  int ans;
  if (A == 0) ans = C * C - B;
  if (B == 0) ans = C * C - A;
  if (C == 0) {
    int q = sqrt(A + B);
    for (int i = q - 1; i <= q + 1; i++) {
      if (i * i == A + B) {
        ans = i;
        break;
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
