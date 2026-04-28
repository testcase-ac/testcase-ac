#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int board[MAX][MAX];
bool watered[MAX * MAX + 30];
tuple<int, int, int, int> gmv[MAX * MAX + 30];
int parent[MAX * MAX + 30];

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

int main() {
  fast_io();

  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    cin >> board[i][j];
    parent[i * m + j] = i * m + j;
  }

  for (int wt = 1; wt <= q; wt++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--; b--;
    board[a][b] -= c;

    int cg = a * m + b;
    watered[cg] = true;

    int ra = a, rb = b, rc = board[a][b], rt = wt;
    if (a > 0 && watered[(a - 1) * m + b]) {
      auto [ca, cb, cc, ct] = gmv[Find((a - 1) * m + b)];
      if (cc < rc) ra = ca, rb = cb, rc = cc, rt = ct;
      else if (cc == rc && ct < rt) ra = ca, rb = cb, rc = cc, rt = ct;
      Union((a - 1) * m + b, cg);
    }
    if (a < n - 1 && watered[(a + 1) * m + b]) {
      auto [ca, cb, cc, ct] = gmv[Find((a + 1) * m + b)];
      if (cc < rc) ra = ca, rb = cb, rc = cc, rt = ct;
      else if (cc == rc && ct < rt) ra = ca, rb = cb, rc = cc, rt = ct;
      Union((a + 1) * m + b, cg);
    }
    if (b > 0 && watered[a * m + b - 1]) {
      auto [ca, cb, cc, ct] = gmv[Find(a * m + b - 1)];
      if (cc < rc) ra = ca, rb = cb, rc = cc, rt = ct;
      else if (cc == rc && ct < rt) ra = ca, rb = cb, rc = cc, rt = ct;
      Union(a * m + b - 1, cg);
    }
    if (b < m - 1 && watered[a * m + b + 1]) {
      auto [ca, cb, cc, ct] = gmv[Find(a * m + b + 1)];
      if (cc < rc) ra = ca, rb = cb, rc = cc, rt = ct;
      else if (cc == rc && ct < rt) ra = ca, rb = cb, rc = cc, rt = ct;
      Union(a * m + b + 1, cg);
    }

    gmv[Find(cg)] = {ra, rb, rc, rt};
    cout << ra + 1 << ' ' << rb + 1 << '\n';
  }
}
