#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;

void solve() {
  ll N, M, K; cin >> N >> M >> K;
  vector<pair<ll, ll>> A, B;
  for (int i = 0; i < M; ++i) {
    ll l, r; cin >> l >> r;
    A.emplace_back(l, r);
  }
  sort(A.begin(), A.end());

  ll lpos = 0;
  for (auto& [l, r] : A) {
    if (lpos <= l - 1) B.emplace_back(lpos, l - 1);
    lpos = r + 1;
  }
  if (lpos <= K - 1) B.emplace_back(lpos, K - 1);

  ll left = 0, right = K;
  while (left < right) {
    ll mid = (left + right) / 2;

    ll lsta = -INF, cnt = 0;
    for (auto& [l, r] : B) {
      ll sta = max(lsta + mid, l);
      ll free = max(0LL, r - sta + 1);
      if (free == 0) continue;

      ll add = (free + mid - 1) / mid;
      cnt += add;
      lsta = sta + (add - 1) * mid;
    }

    if (cnt >= N) left = mid + 1;
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
