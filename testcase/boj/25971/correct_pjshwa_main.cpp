#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;
using tiii = tuple<int, int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll dist(int sx, int sy, int ex, int ey) {
  return 1LL * (ex - sx) * (ex - sx) + 1LL * (ey - sy) * (ey - sy);
}

void solve() {
  ll N, K, R, Q;
  cin >> N >> K >> R >> Q;

  vector<tii> A(K);
  for (int i = 0; i < K; ++i) {
    int x, y, z;
    cin >> x >> y >> z;
    A[i] = {x, y, z};
  }

  vector<tiii> B(Q);
  for (int i = 0; i < Q; ++i) {
    int x, y, z;
    cin >> x >> y >> z;
    B[i] = {x, y, z, i};
  }
  sort(B.begin(), B.end());

  vector<int> ansv(Q); int ai = 0;
  for (int i = 0; i < Q; i++) {
    auto [j, x, y, qi] = B[i];
    while (ai < K - 1 && get<0>(A[ai + 1]) <= j) ai++;

    auto [d, tx, ty] = A[ai]; char dir;
    if (ai == K - 1) {
      auto [_, px, py] = A[ai - 1];
      if (px == tx) dir = py > ty ? 'S' : 'N';
      else dir = px > tx ? 'W' : 'E';
    }
    else {
      auto [_, nx, ny] = A[ai + 1];
      if (nx == tx) dir = ny > ty ? 'N' : 'S';
      else dir = nx > tx ? 'E' : 'W';
    }

    int ans = -1;
    if (dir == 'N') {
      int cx = tx, cy = ty + (j - d);
      if (x < tx && dist(x, y, cx, cy) <= R * R) ans = 0;
      if (x > tx && dist(x, y, cx, cy) <= R * R) ans = 1;
    }
    if (dir == 'S') {
      int cx = tx, cy = ty - (j - d);
      if (x < tx && dist(x, y, cx, cy) <= R * R) ans = 1;
      if (x > tx && dist(x, y, cx, cy) <= R * R) ans = 0;
    }
    if (dir == 'W') {
      int cx = tx - (j - d), cy = ty;
      if (y < ty && dist(x, y, cx, cy) <= 1LL * R * R) ans = 0;
      if (y > ty && dist(x, y, cx, cy) <= 1LL * R * R) ans = 1;
    }
    if (dir == 'E') {
      int cx = tx + (j - d), cy = ty;
      if (y < ty && dist(x, y, cx, cy) <= 1LL * R * R) ans = 1;
      if (y > ty && dist(x, y, cx, cy) <= 1LL * R * R) ans = 0;
    }

    ansv[qi] = ans;
  }

  for (int i = 0; i < Q; ++i) {
    if (ansv[i] == -1) cout << "gori\n";
    else if (ansv[i] == 0) cout << "safe\n";
    else cout << "unsafe\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
