#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int parent[9];
int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void solve() {
  vector<pii> a;
  vector<int> xs, ys;
  for (int i = 0; i < 3; i++) {
    int x, y;
    cin >> x >> y;
    a.push_back({x, y});
    xs.push_back(x);
    ys.push_back(y);
  }
  sort(xs.begin(), xs.end());
  sort(ys.begin(), ys.end());

  vector<int> pts;
  for (auto [x, y] : a) {
    bool f = false;

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        int px = xs[i], py = ys[j];
        if (x == px && y == py) {
          pts.push_back(i * 3 + j);
          f = true;
          break;
        }
      }
      if (f) break;
    }
  }

  ll mval = -1;
  for (int s = 0; s < (1 << 18); s++) {
    for (int i = 0; i < 9; i++) parent[i] = i;
    ll cur = 0;

    for (int b = 0; b < 9; b++) {
      if (!(s & (1 << b))) continue;
      int i = b / 3, j = b % 3;
      if (j == 0) Union(i * 3, i * 3 + 1), cur += abs(ys[0] - ys[1]);
      else if (j == 1) Union(i * 3 + 1, i * 3 + 2), cur += abs(ys[1] - ys[2]);
      else Union(i * 3 + 2, i * 3), cur += abs(ys[2] - ys[0]);
    }

    for (int b = 9; b < 18; b++) {
      if (!(s & (1 << b))) continue;
      int i = (b - 9) / 3, j = b % 3;
      if (i == 0) Union(j, 3 + j), cur += abs(xs[0] - xs[1]);
      else if (i == 1) Union(3 + j, 6 + j), cur += abs(xs[1] - xs[2]);
      else Union(6 + j, j), cur += abs(xs[2] - xs[0]);
    }

    if (Find(pts[0]) == Find(pts[1]) && Find(pts[1]) == Find(pts[2])) {
      if (mval == -1 || mval > cur) mval = cur;
    }
  }

  for (int s = 0; s < (1 << 18); s++) {
    for (int i = 0; i < 9; i++) parent[i] = i;
    ll cur = 0;

    for (int b = 0; b < 9; b++) {
      if (!(s & (1 << b))) continue;
      int i = b / 3, j = b % 3;
      if (j == 0) Union(i * 3, i * 3 + 1), cur += abs(ys[0] - ys[1]);
      else if (j == 1) Union(i * 3 + 1, i * 3 + 2), cur += abs(ys[1] - ys[2]);
      else Union(i * 3 + 2, i * 3), cur += abs(ys[2] - ys[0]);
    }

    for (int b = 9; b < 18; b++) {
      if (!(s & (1 << b))) continue;
      int i = (b - 9) / 3, j = b % 3;
      if (i == 0) Union(j, 3 + j), cur += abs(xs[0] - xs[1]);
      else if (i == 1) Union(3 + j, 6 + j), cur += abs(xs[1] - xs[2]);
      else Union(6 + j, j), cur += abs(xs[2] - xs[0]);
    }

    if (Find(pts[0]) == Find(pts[1]) && Find(pts[1]) == Find(pts[2]) && mval == cur) {
      vector<pair<pii, pii>> ans;

      for (int b = 0; b < 9; b++) {
        if (!(s & (1 << b))) continue;
        int i = b / 3, j = b % 3;
        if (j == 0) ans.push_back({{xs[i], ys[0]}, {xs[i], ys[1]}});
        else if (j == 1) ans.push_back({{xs[i], ys[1]}, {xs[i], ys[2]}});
        else ans.push_back({{xs[i], ys[2]}, {xs[i], ys[0]}});
      }

      for (int b = 9; b < 18; b++) {
        if (!(s & (1 << b))) continue;
        int i = (b - 9) / 3, j = b % 3;
        if (i == 0) ans.push_back({{xs[0], ys[j]}, {xs[1], ys[j]}});
        else if (i == 1) ans.push_back({{xs[1], ys[j]}, {xs[2], ys[j]}});
        else ans.push_back({{xs[2], ys[j]}, {xs[0], ys[j]}});
      }

      cout << ans.size() << '\n';
      for (auto [p1, p2] : ans) {
        cout << p1.first << ' ' << p1.second << ' ';
        cout << p2.first << ' ' << p2.second << '\n';
      }

      return;
    }
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
