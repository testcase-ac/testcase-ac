#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int ans = 0;
  for (int i = 0; i < N; i++) {
    int A[7]; for (int &x : A) cin >> x;
    int score = max(A[0], A[1]);

    sort(A + 2, A + 7, greater<int>());
    score += A[2] + A[3];
    ans = max(ans, score);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
