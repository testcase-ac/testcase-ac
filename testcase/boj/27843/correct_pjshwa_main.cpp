#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 500, INF = 1e18;
ll A[MAX + 1], P[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i], P[i] = P[i - 1] + A[i];

  vector<tll> V;
  for (int i = 1; i <= N; i++) for (int j = i; j <= N; j++) {
    ll sum = P[j] - P[i - 1];
    V.emplace_back(sum, i, j);
  }
  sort(V.begin(), V.end());

  int z = V.size();
  for (int i = 1; i <= N; i++) {
    ll ans = INF;

    for (int j = 0; j < z - 1; j++) {
      auto [s1, l1, r1] = V[j];
      auto [s2, l2, r2] = V[j + 1];

      bool b1 = l1 <= i && i <= r1;
      bool b2 = l2 <= i && i <= r2;

      if (b1 ^ b2) ans = min(ans, s2 - s1);
    }

    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
