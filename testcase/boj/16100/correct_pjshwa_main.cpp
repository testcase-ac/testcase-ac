#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
ll H[MAXN], C[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> H[i];
  if (N == 1) return cout << H[0] << '\n', void();

  ll ans; ans = C[N - 1] = H[N - 1];
  for (int i = N - 2; i >= 1; --i) {
    ll rep = (C[i + 1] - 1) / H[i] + 1;
    C[i] = H[i] * rep;
    ans += C[i];
  }
  C[0] = H[0]; ans += C[0];

  ll cur = ans;
  for (int i = 1; i < N; ++i) {
    cur -= C[i];
    ll rep = (C[i - 1] - 1) / H[i] + 1;
    C[i] = H[i] * rep;
    cur += C[i];
    ans = min(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
