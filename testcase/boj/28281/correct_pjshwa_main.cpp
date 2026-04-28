#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX];

void solve() {
  int N, X; cin >> N >> X;
  for (int i = 0; i < N; i++) cin >> A[i];

  int ans = (A[0] + A[1]) * X;
  for (int i = 1; i < N - 1; i++) {
    ans = min(ans, (A[i] + A[i + 1]) * X);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
