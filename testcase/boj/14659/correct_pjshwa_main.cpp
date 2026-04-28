#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e4;
int a[MAX];

void solve() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) cin >> a[i];

  int ans = 0, streak = 1, val = a[0];
  for (int i = 1; i < n; i++) {
    if (a[i] < val) streak++;
    else {
      ans = max(ans, streak - 1);
      val = a[i];
      streak = 1;
    }
  }
  ans = max(ans, streak - 1);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
