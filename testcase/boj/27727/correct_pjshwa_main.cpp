#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
ll A[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];
  ll K; cin >> K;

  ll lim = 0, run = 0;
  for (int i = 1; i <= N; i++) {
    run = max(run, A[i]);
    if (A[i] < run) lim = run;
  }

  ll pre = 0;
  for (int i = 1; i <= N; i++) {
    if (A[i] < lim) {
      pre += lim - A[i];
      A[i] = lim;
    }
  }
  if (pre > K) return cout << "0\n", void();

  ll ans;
  if (pre) K -= pre, ans = 1;
  else ans = 0;

  for (int i = 1; i < N; i++) {
    if (A[i] == A[i + 1]) continue;

    ll step = A[i + 1] - A[i];
    ll rout = step * i;
    if (rout >= K) {
      ans += K / i;
      K = 0;
      break;
    }
    else {
      ans += step;
      K -= rout;
    }
  }
  ans += K / N;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
