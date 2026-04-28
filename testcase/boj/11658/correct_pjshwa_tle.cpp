#include <bits/stdc++.h>
using namespace std;

const int MAX = 1 << 10, M_ASSIGN = 0, M_ADD = 1;
int P[MAX + 1][MAX + 1];
int T[1 << 21];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct Segtree2d {
  int n, m;

  void init(int n, int m) {
    this -> n = n;
    this -> m = m;
    build(1, 1, 1, n, m);
  }

  void build(int node, int a1, int b1, int a2, int b2) {
    if (a1 > a2 or b1 > b2) return;

    if (a1 == a2 and b1 == b2) {
      T[node] = P[a1][b1];
      return;
    }

    build(4 * node + 0, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2 );
    build(4 * node + 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2);
    build(4 * node + 2, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2);
    build(4 * node + 3, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2);
    T[node] = T[4 * node + 0] + T[4 * node + 1] + T[4 * node + 2] + T[4 * node + 3];
  }
 
  int query(int node, int a1, int b1, int a2, int b2, int x1, int y1, int x2, int y2) {
    if (x1 > a2 or y1 > b2 or x2 < a1 or y2 < b1 or a1 > a2 or b1 > b2) return 0;
    if (x1 <= a1 and y1 <= b1 and a2 <= x2 and b2 <= y2) return T[node];

    int res = 0;
    res += query(4 * node + 0, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, x1, y1, x2, y2);
    res += query(4 * node + 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2, x1, y1, x2, y2);
    res += query(4 * node + 2, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2, x1, y1, x2, y2);
    res += query(4 * node + 3, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2, x1, y1, x2, y2);
    return res;
  }
 
  int query(int x1, int y1, int x2, int y2) {
    return query(1, 1, 1, n, m, x1, y1, x2, y2);
  }

  void update(int node, int a1, int b1, int a2, int b2, int x, int y, int diff, int mode) {
    if (a1 > a2 or b1 > b2) return;
    if (x > a2 or y > b2 or x < a1 or y < b1) return;
    if (x == a1 and y == b1 and x == a2 and y == b2) {
      mode == M_ASSIGN ? T[node] = diff : T[node] += diff;
      return;
    }

    update(4 * node + 0, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, x, y, diff, mode);
    update(4 * node + 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2, x, y, diff, mode);
    update(4 * node + 2, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2, x, y, diff, mode);
    update(4 * node + 3, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2, x, y, diff, mode);
    T[node] = T[4 * node + 0] + T[4 * node + 1] + T[4 * node + 2] + T[4 * node + 3];
  }

  void assign(int x, int y, int val) {
    update(1, 1, 1, n, m, x, y, val, M_ASSIGN);
  }

  void update(int x, int y, int val) {
    update(1, 1, 1, n, m, x, y, val, M_ADD);
  }
};

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> P[i][j];

  Segtree2d s;
  s.init(n, n);

  while (m--) {
    int w, a, b, c, d;
    cin >> w >> a >> b >> c;

    if (w == 0) s.assign(a, b, c);
    else {
      cin >> d;
      cout << s.query(a, b, c, d) << '\n';
    }
  }
}
