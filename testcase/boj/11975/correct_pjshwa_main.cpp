#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  set<pii> v;
  set<pair<pii, pii>> e;

  int n;
  string op;
  cin >> n >> op;

  int x = 0, y = 0;
  v.insert({x, y});
  for (int i = 0; i < n; i++) {
    int nx = x, ny = y;
    if (op[i] == 'N') ny++;
    if (op[i] == 'S') ny--;
    if (op[i] == 'E') nx++;
    if (op[i] == 'W') nx--;

    v.insert({nx, ny});
    e.insert({{x, y}, {nx, ny}});
    e.insert({{nx, ny}, {x, y}});

    x = nx, y = ny;
  }

  int vsz = v.size(), esz = e.size() / 2;
  cout << (esz - vsz + 1) << '\n';
}
