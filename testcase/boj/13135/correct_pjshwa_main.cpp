#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
bool oi[MAX];
int diff[MAX];

int main() {
  fast_io();

  int n, s = 0;
  cin >> n;
  vector<pii> xs, ys;
  for (int i = 0; i < n; i++) {
    int ai, bi;
    cin >> ai >> bi;
    diff[i] = ai - bi;
    s += diff[i];

    xs.push_back({max(ai, bi), i});
    ys.push_back({ai + bi, i});
  }
  xs.push_back({0, n});
  ys.push_back({0, n});
  sort(all(xs));
  sort(all(ys));
  reverse(all(xs));
  reverse(all(ys));

  ll ans = 0;
  int xmt, ymt = 100000, nxmt, nymt, xi, yi = 0;
  int od = s, nd;
  while (yi < n) {
    while (ys[yi].first >= ymt) {
      od -= diff[ys[yi].second];
      oi[ys[yi].second] = true;
      yi++;
    }
    nymt = ys[yi].first;

    xi = 0, xmt = 100000;
    nd = od;
    while (xi < n) {
      while (xs[xi].first >= xmt) {
        if (!oi[xs[xi].second]) nd -= diff[xs[xi].second];
        xi++;
      }
      nxmt = xs[xi].first;

      if (nd > 0) ans += (ll)(ymt - nymt) * (xmt - nxmt);

      xmt = nxmt;
    }

    ymt = nymt;
  }

  cout << ans << '\n';
}
