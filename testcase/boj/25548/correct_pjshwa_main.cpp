#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll d(ll U) {
  int ans = 0;
  for (int f = 1; f * f <= U; f++) {
    if (U % f) continue;
    int s = U / f;
    ans++;
    if (f != s) ans++;
  }
  return ans;
}

ll f(ll U) {
  int ans = 0;
  for (int f = 1; f * f <= U; f++) {
    if (U % f) continue;
    int s = U / f;
    ans += d(f);
    if (f != s) ans += d(s);
  }
  return ans;
}

// sum of d(1)..d(N)
ll sum_d(ll N) {
  ll ret = 0, q = sqrt(N);
  for (int i = 1; i <= q; i++) ret += N / i;
  ret = 2 * ret - q * q;
  return ret;
}

void solve() {
  ll N;
  cin >> N;

  // ll sumd = 0;
  // for (int i = 1; i <= N; i++) {
  //   // cout << "d(" << i << ") = " << d(i) << '\n';
  //   sumd += d(i);
  // }

  ll q = sqrt(N), ans = 0;
  for (int i = 1; i <= q; i++) ans += (N / i) * d(i);

  int last = N;
  for (int i = 1; i < N / q; i++) {
    int s = N / (i + 1) + 1;
    ans = (ans + (sum_d(last) - sum_d(s - 1)) * i);
    last = s - 1;
  }

  cout << ans << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
