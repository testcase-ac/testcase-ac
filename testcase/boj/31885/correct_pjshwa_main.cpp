#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll N, Ex, Ey;
set<pll> items;

void solve_K1() {
  ll dis = abs(Ex) + abs(Ey);
  if (dis == 1) {
    cout << "1\n";
    exit(0);
  }
}

void solve_K2() {
  for (auto& [dx, dy] : items) {
    if (dx == Ex && dy == Ey) {
      cout << "2\n";
      exit(0);
    }
  }
  ll dis = abs(Ex) + abs(Ey);
  if (dis == 2) {
    cout << "2\n";
    exit(0);
  }
}

void solve_K3() {
  for (auto& [dx, dy] : items) {
    if (abs(dx - Ex) + abs(dy - Ey) == 1) {
      cout << "3\n";
      exit(0);
    }
  }
  ll dis = abs(Ex) + abs(Ey);
  if (dis == 3) {
    cout << "3\n";
    exit(0);
  }
}

void solve_K4() {
  for (auto& [dx, dy] : items) {
    if (abs(dx - Ex) + abs(dy - Ey) == 2) {
      cout << "4\n";
      exit(0);
    }
    ll rx = Ex - dx, ry = Ey - dy;
    if (items.count({rx, ry})) {
      cout << "4\n";
      exit(0);
    }
  }
  ll dis = abs(Ex) + abs(Ey);
  if (dis == 4) {
    cout << "4\n";
    exit(0);
  }
}

void solve_K5() {
  for (auto& [dx, dy] : items) {
    if (abs(dx - Ex) + abs(dy - Ey) == 3) {
      cout << "5\n";
      exit(0);
    }
    // check adjacent points
    for (auto& [Px, Py] : {pll{Ex, Ey + 1}, pll{Ex, Ey - 1}, pll{Ex + 1, Ey}, pll{Ex - 1, Ey}}) {
      ll rx = Px - dx, ry = Py - dy;
      if (items.count({rx, ry})) {
        cout << "5\n";
        exit(0);
      }
    }
  }
  ll dis = abs(Ex) + abs(Ey);
  if (dis == 5) {
    cout << "5\n";
    exit(0);
  }
}

void solve() {
  int K; cin >> N >> K;
  for (int i = 0; i < N; ++i) {
    ll x, y; cin >> x >> y;
    items.insert({x, y});
  }
  cin >> Ex >> Ey;

  if (K >= 1) solve_K1();
  if (K >= 2) solve_K2();
  if (K >= 3) solve_K3();
  if (K >= 4) solve_K4();
  if (K >= 5) solve_K5();
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
