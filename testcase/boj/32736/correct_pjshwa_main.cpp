#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
ll A[MAXN + 1], P[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i], P[i] = A[i] + P[i - 1];

  ll ans = 0; map<ll, int> tal;
  for (int i = 1; i <= N; ++i) {
    ans += tal[P[i - 1] - A[i]];
    ++tal[P[i] + A[i]];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
