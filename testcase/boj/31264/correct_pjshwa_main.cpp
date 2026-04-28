#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, M, A; cin >> N >> M >> A;

  vector<int> S(N);
  for (int i = 0; i < N; ++i) cin >> S[i];
  sort(S.begin(), S.end());

  ll l = 1, r = 1e5 + 1;
  while (l < r) {
    ll m = (l + r) / 2;
    ll cur = 0, ini = m;

    int i = 0;
    for (int j = 0; j < M; ++j) {
      while (i < N && S[i] <= ini) ++i;
      if (i == 0) break;
      cur += S[i - 1];
      ini += S[i - 1];
    }

    if (cur < A) l = m + 1;
    else r = m;
  }

  cout << l << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
