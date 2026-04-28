#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N = 12, T; cin >> T;
  vector<int> A(N); for (int& x : A) cin >> x;

  int ans = 0;
  for (int s = 1; s < N - 1; s++) {
    if (A[s] <= A[s - 1]) continue;

    int bnd = A[s - 1], mmin = A[s];
    for (int e = s; e < N - 1; e++) {
      if (A[e + 1] < mmin && bnd < mmin) ans++;
      mmin = min(mmin, A[e + 1]);
    }
  }

  cout << T << ' ' << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
