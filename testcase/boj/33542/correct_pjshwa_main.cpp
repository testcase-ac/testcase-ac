#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;

void solve() {
  ll A, B, N, maxs = INF, tli = -1, tri = -1; cin >> A >> B >> N;
  vector<tuple<ll, ll, int>> V;
  for (int i = 1; i <= N; ++i) {
    ll l, r; cin >> l >> r;
    V.emplace_back(l, r, i);
  }

  auto update_conditional = [&](ll add, int li, int ri) {
    if (B + add > A && maxs > B + add) {
      maxs = B + add;
      tli = li, tri = ri;
    }
  };

  sort(V.begin(), V.end());
  for (auto& [_, r, ri] : V) {
    ll target = max(0LL, A + 1 - B - r);
    auto it = lower_bound(V.begin(), V.end(), make_tuple(target, 0, 0));
    for (int t = 0; t < 3; ++t) {
      if (it == V.end()) break;
      auto [l, _, li] = *it;
      update_conditional(li == ri ? 0 : l + r, li, ri);
      ++it;
    }
  }

  sort(V.begin(), V.end(), [](auto& a, auto& b) {
    auto [al, ar, _] = a;
    auto [bl, br, __] = b;
    if (ar != br) return ar < br;
    return al < bl;
  });
  for (auto& [l, _, li] : V) {
    ll target = max(0LL, A + 1 - B - l);
    auto it = lower_bound(V.begin(), V.end(), make_tuple(0, target, 0));
    for (int t = 0; t < 3; ++t) {
      if (it == V.end()) break;
      auto [_, r, ri] = *it;
      update_conditional(li == ri ? 0 : l + r, li, ri);
      ++it;
    }
  }

  // Deliberately aim for zero score
  update_conditional(0, -1, -1);

  // Aim for one score only
  for (auto& [l, r, i] : V) {
    update_conditional(l, i, -1);
    update_conditional(r, -1, i);
  }

  if (maxs == INF) cout << "No\n";
  else cout << tli << ' ' << tri << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
