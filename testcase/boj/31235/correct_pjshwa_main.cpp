#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  int ans = 0, li = 0, lv = A[0];
  for (int i = 1; i < N; ++i) {
    if (A[i] < lv) continue;
    lv = A[i];
    ans = max(ans, i - li);
    li = i;
  }
  ans = max(ans, N - li);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
