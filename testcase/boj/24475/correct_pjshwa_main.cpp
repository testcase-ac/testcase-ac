#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3e5;
pll A[MAX + 1];

void solve() {
  ll N, M; cin >> N >> M;
  for (int i = 1; i <= N; i++) cin >> A[i].first;
  for (int i = 1; i <= N; i++) cin >> A[i].second, A[i].first = max(A[i].first, A[i].second);

  ll left = 1, right = 1e18;
  right++;
  while (left < right) {
    ll mid = (left + right) / 2, trials = N * M;

    vector<ll> acc(N + 1);
    for (int i = 1; i <= N; i++) {
      auto [a, _] = A[i];

      ll use = min({M, (mid - 1) / a + 1, trials});
      trials -= use;
      acc[i] = use * a;
    }

    bool f = true;
    for (int i = 1; i <= N; i++) {
      if (acc[i] >= mid) continue;

      auto [_, b] = A[i];
      ll use = min(trials, (mid - acc[i] - 1) / b + 1);
      trials -= use;
      acc[i] += use * b;

      if (acc[i] < mid) {
        f = false;
        break;
      }
    }

    if (f) left = mid + 1;
    else right = mid;
  }

  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
