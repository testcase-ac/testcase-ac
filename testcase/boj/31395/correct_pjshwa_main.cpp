#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  ll ans = 0, streak = 1;
  for (int i = 1; i < N; ++i) {
    if (A[i] > A[i - 1]) ++streak;
    else {
      ans += streak * (streak + 1) / 2;
      streak = 1;
    }
  }
  ans += streak * (streak + 1) / 2;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
