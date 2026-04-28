#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, R; cin >> N >> M >> R;
  R *= 2;

  vector<int> A(N);
  for (int& x : A) cin >> x;
  sort(A.begin(), A.end());

  vector<int> B(M);
  for (int& x : B) cin >> x;
  sort(B.begin(), B.end());

  int ans = -1;
  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    int dif = A[j] - A[i], hgt = R / dif;

    // must not be bigger than hgt
    auto it = upper_bound(B.begin(), B.end(), hgt);
    if (it == B.begin()) continue;

    ans = max(ans, dif * *prev(it));
  }

  if (ans == -1) cout << "-1\n";
  else if (ans & 1) cout << ans / 2 << ".5\n";
  else cout << ans / 2 << ".0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
