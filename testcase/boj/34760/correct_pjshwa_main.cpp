#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N = 15;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  int maxv = *max_element(A.begin(), A.end());
  int maxc = 0;
  for (int i = 0; i < N; ++i) maxc += (A[i] == maxv);

  int ans = maxv + 1;
  if (A.back() == maxv && maxc == 1) --ans;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
