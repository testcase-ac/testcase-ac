#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;

void solve() {
  ll S[3];
  for (int i = 0; i < 3; i++) cin >> S[i];
  for (int i = 0; i < 3; i++) {
    int x; cin >> x; S[i] -= x;
  }

  ll ans = 0;
  if (S[0] < 0) {
    ans -= S[0];
    S[1] += S[0] * 11;
    S[0] = 0;
  }
  if (S[2] < 0) {
    ll d = (-S[2] + 8) / 9;
    ans += d;
    S[1] -= d;
    S[2] += d * 9;
  }

  ll mmv = INF, need = -S[1];
  if (need <= 0) return cout << ans << '\n', void();

  assert(S[0] >= 0 && S[1] < 0 && S[2] >= 0);
  for (ll i = 0; i <= S[0]; i++) {
    ll acc = i * 9;
    if (acc >= need) {
      mmv = min(mmv, i);
      continue;
    }

    ll j = need - acc;
    if (j * 11 <= S[2]) mmv = min(mmv, i + j);
  }

  if (mmv == INF) cout << "-1\n";
  else cout << ans + mmv << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
