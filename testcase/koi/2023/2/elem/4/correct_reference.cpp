#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  struct Meat { int s, e, t; } a[n];
  int ss[n];
  for(int i = 0; i < n; ++i) cin >> a[i].s >> a[i].e >> a[i].t;
  sort(a, a + n, [&](Meat &p, Meat &q) { return p.s < q.s; });
  for(int i = 0; i < n; ++i) ss[i] = a[i].s;

  const int sz = 262144;
  int d[2 * sz], p[2 * sz];
  iota(p + sz, p + 2 * sz, 0);
  for(int i = 0; i < n; ++i) d[i + sz] = a[i].e;
  const auto mrg = [&](int i) {
    int ii = 2 * i + (d[2 * i] < d[2 * i + 1]);
    d[i] = d[ii]; p[i] = p[ii];
  };
  for(int i = sz - 1; i; --i) mrg(i);

  using ll = long long;
  const auto f = [&](int x, int y) {
    ll r = 0;
    while(1) {
      int ci = -1;
      for(int i = x + sz; i; i /= 2) if(~i & 1) {
        if(d[i] >= y) { ci = p[i]; break; }
        --i;
      }
      if(ci < 0) break;
      r += a[ci].t;
      d[ci += sz] = -1;
      for(ci /= 2; ci; ci /= 2) mrg(ci);
    }
    return r;
  };

  while(m--) {
    int x, y;
    cin >> x >> y;
    int px = int(upper_bound(ss, ss + n, x) - ss - 1);
    int py = int(upper_bound(ss, ss + n, y) - ss - 1);
    cout << f(px, y + 1) << '\n';
    f(px, x + 1);
    f(py, y + 1);
  }
  return 0;
}