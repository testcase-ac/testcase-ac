#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int a, b, w, M; cin >> a >> b >> w >> M;

  vector<int> A(a);
  for (auto& x : A) cin >> x;
  sort(A.begin(), A.end());

  vector<int> B(w);
  for (int i = 0; i < w; ++i) {
    int maxv = 0, x;
    for (int j = 0; j < b; ++j) cin >> x, maxv = max(maxv, x);
    B[i] = maxv;
  }
  sort(B.begin(), B.end(), greater<int>());

  ll ans = 0;
  for (int i = 0; i < w; ++i) {
    int maxv = B[i];
    for (int j = 0; j < M - b; ++j) {
      if (A.empty()) break;
      maxv = max(maxv, A.back());
      A.pop_back();
    }
    ans += 2 * (maxv - 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
