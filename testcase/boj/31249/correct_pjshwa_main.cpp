#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 400, INF = 0x3f3f3f3f;
int cdist[MAXN][MAXN][2];
using T = tuple<int, int, int>;

pll bf(int n, int m) {
  for (int K = 1; K <= n + m; ++K) {
    memset(cdist, 0x3f, sizeof cdist);

    queue<T> q;
    q.emplace(n, m, 0); cdist[n][m][0] = 0;

    while (!q.empty()) {
      auto [en, em, d] = q.front(); q.pop();

      // cout << "en = " << en << ", em = " << em << ", d = " << d << ", cdist = " << cdist[en][em][d] << endl;

      int wn = n - en, wm = m - em;

      if (d == 0) {
        // East to west
        for (int bn = 0; bn <= min(K, en); ++bn) for (int bm = 0; bm <= min(K, em); ++bm) {
          if (bn + bm > K) continue;

          int rn = en - bn, rm = em - bm;
          if (rn > 0 && rm > 0) continue;

          int nwn = wn + bn, nwm = wm + bm;
          int nen = n - nwn, nem = m - nwm;
          if (cdist[nen][nem][1] == INF) {
            cdist[nen][nem][1] = cdist[en][em][d] + 1;
            q.emplace(nen, nem, 1);
          }
        }
      }
      else {
        // West to east
        for (int bn = 0; bn <= min(K, wn); ++bn) for (int bm = 0; bm <= min(K, wm); ++bm) {
          if (bn + bm > K) continue;

          int rn = wn - bn, rm = wm - bm;
          if (rn > 0 && rm > 0) continue;

          int nen = en + bn, nem = em + bm;
          if (cdist[nen][nem][0] == INF) {
            cdist[nen][nem][0] = cdist[en][em][d] + 1;
            q.emplace(nen, nem, 0);
          }
        }
      }
    }

    if (cdist[0][0][1] != INF) {
      return {K, cdist[0][0][1]};
    }
  }

  return {-1, -1};

}

pll gf(int n, int m) {
  if (n > m) swap(n, m);

  ll k, w;
  if (n == m) {
    k = n;
    w = 3;
  }
  else if (2 * n >= m) {
    k = n;
    w = 7;
  }
  else {
    k = n + 1;

    ll d = m - 2 * n;
    if (d <= 2) w = 7;
    else w = 7 + 2 * (d - 2);
  }

  return {k, w};
}

void solve() {
  ll n, m; cin >> n >> m;

  ll k, w;
  if (n <= 10 && m <= 10) tie(k, w) = bf(n, m);
  else tie(k, w) = gf(n, m);
  cout << k << ' ' << w << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
