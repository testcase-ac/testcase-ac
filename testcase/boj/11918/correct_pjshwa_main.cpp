#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 150'000;
ll A[MAXN];

void solve() {
  int N, L; cin >> N >> L;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N);

  vector<pll> As, Bs;
  auto merge = [&](vector<pll>& U, pll V) {
    if (U.empty()) {
      U.push_back(V);
      return;
    }

    while (!U.empty() && U.back().second >= V.first) {
      V.first = min(V.first, U.back().first);
      V.second = max(V.second, U.back().second);
      U.pop_back();
    }
    U.push_back(V);
  };

  for (int i = 0; i < N; ++i) {
    if (i & 1) merge(As, pll(A[i] - L, A[i] + L));
    else merge(Bs, pll(A[i] - L, A[i] + L));
  }

  // overlapping area
  vector<pll> Cs; int Az = As.size(), Bz = Bs.size();
  for (int i = 0, j = 0; i < Az && j < Bz;) {
    auto& [as, ae] = As[i]; auto& [bs, be] = Bs[j];
    ll s = max(as, bs), e = min(ae, be);
    if (s < e) Cs.push_back(pll(s, e));
    ae < be ? ++i : ++j;
  }

  ll ans = 0;
  for (auto [s, e] : Cs) ans += e - s;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
