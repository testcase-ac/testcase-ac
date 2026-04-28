#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  int b[11];
  memset(b, -1, sizeof(b));

  for (int i = 0; i < n; i++) {
    int bi, di;
    cin >> bi >> di;
    b[di] = max(b[di], bi);
  }

  int ans = 0;
  for (int i = 1; i <= 10; i++) {
    if (b[i] == -1) return cout << "MOREPROBLEMS\n", void();
    ans += b[i];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
