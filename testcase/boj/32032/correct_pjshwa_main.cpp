#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, D; cin >> N >> D;
  vector<ll> W, E;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    if (x < 0) W.push_back(x);
    else E.push_back(x);
  }
  sort(W.begin(), W.end(), greater<ll>());
  sort(E.begin(), E.end());

  if (W.empty()) return cout << 2 * E[N - 1] + D << '\n', void();
  if (E.empty()) return cout << -2 * W[N - 1] + D << '\n', void();

  // 0: get W, 1: get E, 2: return W, 3: return E
  ll wmax = W.back(), emax = E.back(), ans = 1e18;
  ll P[4] = {0, 1, 2, 3}, U[4] = {wmax, emax, wmax, emax};

  do {
    int valid = 1, G[2]{};
    for (int i = 0; i < 4; ++i) {
      if (P[i] < 2) G[P[i]] = 1;
      else if (!G[P[i] - 2]) valid = 0;
    }
    if (!valid) continue;

    ll sum = abs(U[P[0]]), S[2]{};
    G[0] = G[1] = 0; G[P[0]] = 1;
    auto add_dist = [&](ll d) {
      sum += d;
      if (G[0]) S[0] += d;
      if (G[1]) S[1] += d;
    };

    for (int i = 1; i < 4; ++i) {
      ll diff = abs(U[P[i]] - U[P[i - 1]]);
      add_dist(diff);

      if (P[i] < 2) G[P[i]] = 1;
      else if (S[P[i] - 2] < D) add_dist(D - S[P[i] - 2]);
    }
    ans = min(ans, sum + abs(U[P[3]]));

  } while (next_permutation(P, P + 4));

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
