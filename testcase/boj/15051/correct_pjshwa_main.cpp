#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A[3];
  cin >> A[0] >> A[1] >> A[2];

  int ans = A[1] + 2 * A[2];
  ans = min(ans, A[0] + A[2]);
  ans = min(ans, 2 * A[0] + A[1]);
  cout << 2 * ans << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
