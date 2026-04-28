#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXK = 1e5;
int base[MAXK + 1], skill[MAXK + 1], s[MAXK + 1], p[MAXK + 1];

void solve() {
  int N, K, C, R; cin >> N >> K >> C >> R;
  for (int i = 1; i <= K; ++i) cin >> base[i];
  for (int i = 1; i <= K; ++i) cin >> s[i];
  for (int i = 1; i <= K; ++i) cin >> p[i];

  int combo = 0, fati = 0; ll ans = 0;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    if (x == 0) {
      combo = 0;
      fati = max(0, fati - R);
    }
    else {
      fati += p[x];
      if (fati > 100) return cout << "-1\n", void();

      ll add = base[x];
      add *= (100 + combo * C);
      add *= (100 + skill[x] * s[x]);
      add /= 10000;
      ans += add;

      ++combo; ++skill[x];
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
