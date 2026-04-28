#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, k; cin >> n >> k;

  vector<int> A(n);
  for (int i = 0; i < n; ++i) cin >> A[i], A[i] -= k;

  map<ll, int> dt; dt[0] = -1;
  int ans = 0, aleft; ll acc = 0;
  for (int i = 0; i < n; ++i) {
    acc += A[i];
    if (dt.count(acc)) {
      if (ans < i - dt[acc]) {
        ans = i - dt[acc];
        aleft = dt[acc] + 2;
      }
    }
    else dt[acc] = i;
  }

  cout << ans;
  if (ans) cout << ' ' << aleft;
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
