#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S;
void solve() {
  set<pii> v;
  set<pair<pii, pii>> e;

  int x = 0, y = 0, n = S.size() - 1;
  v.insert({x, y});
  for (int i = 0; i < n; i++) {
    int nx = x, ny = y;
    if (S[i] == 'U') ny++;
    if (S[i] == 'D') ny--;
    if (S[i] == 'R') nx++;
    if (S[i] == 'L') nx--;

    v.insert({nx, ny});
    e.insert({{x, y}, {nx, ny}});
    e.insert({{nx, ny}, {x, y}});

    x = nx, y = ny;
  }

  int vsz = v.size(), esz = e.size() / 2;
  cout << (esz - vsz + 1) << '\n';
}

int main() {
  fast_io();

  while (cin >> S) {
    if (S == "Q") break;
    solve();
  }
}
