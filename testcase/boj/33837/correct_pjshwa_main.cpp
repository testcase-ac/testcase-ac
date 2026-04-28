#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A.begin(), A.end());

  int g = 0;
  for (int i = 0; i < N - 1; ++i) g = __gcd(g, A[i]);
  int ans = g + A.back();

  A.erase(unique(A.begin(), A.end()), A.end());
  for (int t = 1; t <= A.back(); ++t) {
    int g1 = 0, g2 = 0;
    for (auto& x : A) {
      if (x % t == 0) g1 = __gcd(g1, x);
      else g2 = __gcd(g2, x);
    }
    ans = max(ans, g1 + g2);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
