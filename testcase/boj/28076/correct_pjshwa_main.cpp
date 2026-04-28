#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  for (int& x : A) cin >> x;
  sort(A.begin(), A.end(), greater<int>());

  if (N == 1) cout << A[0] << '\n';
  else if (N == 2) cout << A[0] + A[1] - 1 << '\n';
  else {
    int ans = A[0] - 3, g = (N - 1) / 3 + 1;
    ans += A[g]; ans += A[g + g - (N % 3 == 1)];
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
