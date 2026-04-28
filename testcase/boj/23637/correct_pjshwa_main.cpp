#include <bits/stdc++.h>
using namespace std;

const int MAX = 1 << 11;
const double eps = 1e-9;
int P[MAX + 1][MAX + 1], N = 1000;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int query(int x, int y) {
  int ret = 0;
  for(int i=x; i>0; i -= (i&-i)){
    for(int j=y; j>0; j -= (j&-j)){
      ret += P[i][j];
    }
  }
  return ret;
}

int sum(int x1, int y1, int x2, int y2) {
  return query(x2, y2) - query(x2, y1-1) - query(x1-1, y2) + query(x1-1, y1-1);
}

void update(int x, int y, int val) {
  for(int i = x; i <= N; i += (i&-i)){
    for(int j = y; j <= N; j += (j&-j)){
      P[i][j] += val;
    }
  }
}

int deg(int t) {
  if (t < 0) t += 360;
  return t % 360;
}

void update_ccord(int a, int b) {
  int r = ceil(sqrt(a * a + b * b));
  double t = atan2(a, b) * 180 / M_PI;
  if (t < 0) t += 360;

  if (abs(round(t) - t) < eps) update(r, deg(round(t)) * 2 + 1, 1);
  else update(r, deg(floor(t)) * 2 + 2, 1);
}

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;

  while (n--) {
    int a, b;
    cin >> a >> b;
    update_ccord(a, b);
  }

  while (q--) {
    int w;
    cin >> w;

    if (w == 1) {
      int a, b;
      cin >> a >> b;
      update_ccord(a, b);
    }
    else {
      string dir;
      int a, b, r, c, ll, rl, res;
      cin >> dir >> a >> b >> r >> c;

      if (b == 360) res = query(r, 720);
      else {
        if (dir == "L") ll = deg(a), rl = deg(a + b);
        else ll = deg(a - b), rl = deg(a);

        if (ll > rl) res = sum(1, 1, r, 2 * rl + 1) + sum(1, 2 * ll + 1, r, 720);
        else res = sum(1, 2 * ll + 1, r, 2 * rl + 1);
      }

      if (res == c) cout << "YES\n";
      else cout << "NO " << res << '\n';
    }
  }
}
