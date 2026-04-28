#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;

void solve() {
  int N, K; cin >> N >> K;

  vector<ll> A(K);
  ll min_ch = INF, max_ch = 0;
  for (int i = 0; i < K; i++) {
    cin >> A[i];
    min_ch = min(min_ch, A[i]);
    max_ch = max(max_ch, A[i]);
  }

  ll ans = 0;
  for (int i = 1; i < K; i++) ans += abs(A[i] - A[i - 1]);

  ll min_th = INF, max_th = 0;
  for (int i = 0; i < N - K; i++) {
    ll x; cin >> x;
    min_th = min(min_th, x);
    max_th = max(max_th, x);
  }

  if (min_th < min_ch) {
    ll dif = min_ch - min_th;
    if (A[0] == min_ch || A.back() == min_ch) ans += dif;
    else ans += min({2 * dif, A[0] - min_th, A.back() - min_th});
  }
  if (max_th > max_ch) {
    ll dif = max_th - max_ch;
    if (A[0] == max_ch || A.back() == max_ch) ans += dif;
    else ans += min({2 * dif, max_th - A[0], max_th - A.back()});
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
