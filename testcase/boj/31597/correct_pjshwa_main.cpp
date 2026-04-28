#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
int X[MAXN][MAXN];

void solve() {
  int n; cin >> n;
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> X[i][j];

  vector<int> nr, nc;
  for (int i = 0; i < n; ++i) {
    set<int> U;
    for (int j = 0; j < n; ++j) U.insert(X[i][j]);
    if (U.size() == n) nr.push_back(i);
  }
  for (int j = 0; j < n; ++j) {
    set<int> U;
    for (int i = 0; i < n; ++i) U.insert(X[i][j]);
    if (U.size() == n) nc.push_back(j);
  }

  vector<tuple<int, int, int>> mods;
  while (!nr.empty() && !nc.empty()) {
    int r = nr.back(), c = nc.back();
    nr.pop_back(), nc.pop_back();

    for (int t = 1; t <= n; ++t) {
      X[r][c] = t; int f = 1;
      set<int> ur, uc;
      for (int i = 0; i < n; ++i) {
        ur.insert(X[i][c]);
        uc.insert(X[r][i]);
      }
      if (ur.size() == n || uc.size() == n) continue;
      break;
    }
    mods.emplace_back(r + 1, c + 1, X[r][c]);
  }

  while (!nr.empty()) {
    int r = nr.back(); nr.pop_back();

    for (int j = 0; j < n; ++j) {
      int ot = X[r][j], f = 0;
      for (int t = 1; t <= n; ++t) {
        X[r][j] = t;
        set<int> ur, uc;
        for (int i = 0; i < n; ++i) {
          ur.insert(X[i][j]);
          uc.insert(X[r][i]);
        }
        if (ur.size() == n || uc.size() == n) continue;

        f = 1;
        mods.emplace_back(r + 1, j + 1, t);
        break;
      }
      if (f) break;
      X[r][j] = ot;
    }
  }

  while (!nc.empty()) {
    int c = nc.back(); nc.pop_back();

    for (int i = 0; i < n; ++i) {
      int ot = X[i][c], f = 0;
      for (int t = 1; t <= n; ++t) {
        X[i][c] = t;
        set<int> ur, uc;
        for (int j = 0; j < n; ++j) {
          ur.insert(X[i][j]);
          uc.insert(X[j][c]);
        }
        if (ur.size() == n || uc.size() == n) continue;

        f = 1;
        mods.emplace_back(i + 1, c + 1, t);
        break;
      }
      if (f) break;
      X[i][c] = ot;
    }
  }

  cout << mods.size() << '\n';
  for (auto [r, c, t] : mods) cout << r << ' ' << c << ' ' << t << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
