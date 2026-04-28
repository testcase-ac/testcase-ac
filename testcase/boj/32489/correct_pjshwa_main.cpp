#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i], A[i] -= i;

  auto calc = [&](int T) {
    ll cost = 0;
    for (int i = 0; i < N; ++i) cost += abs(A[i] - T);
    return cost;
  };

  // Ternary search for the optimal T
  int l = *min_element(A, A + N), r = *max_element(A, A + N);
  while (r - l > 2) {
    int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
    ll cost1 = calc(m1), cost2 = calc(m2);
    if (cost1 < cost2) r = m2;
    else l = m1;
  }

  ll ans = LLONG_MAX;
  for (int T = l; T <= r; ++T) ans = min(ans, calc(T));
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
