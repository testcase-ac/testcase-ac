#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct Tri {
  int x, y, r;

  ll area() {
    return (ll)r * r;
  }
};

Tri merge(Tri a, Tri b) {
  if (b.x < a.x) swap(a, b);
  if (
    b.x + b.y < a.x + a.y + a.r &&
    b.x < a.x + a.r &&
    b.y + b.r > a.y
  ) return {
    b.x,
    max(a.y, b.y),
    min(b.y + b.r - max(a.y, b.y), a.x + a.y + a.r - b.x - max(a.y, b.y))
  };
  return {0, 0, 0};
}

Tri a[10];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i].x >> a[i].y >> a[i].r;

  ll ans = 0;
  for (int state = 1; state < (1 << n); ++state) {
    int c = __builtin_popcount(state);
    bool f = true;
    Tri d;
    for (int i = 0; i < n; ++i) {
      if (state & (1 << i)) {
        if (f) d = a[i], f = false;
        else d = merge(d, a[i]);
      }
    }
    ans += d.area() * (c % 2 ? 1 : -1) * (1 << (c - 1));
  }

  cout << ans / 2 << '.' << ((ans & 1) ? 5 : 0) << '\n';
}
