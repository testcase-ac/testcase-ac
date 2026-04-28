#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int d[MAX + 1][MAX + 1][2];
string S, T;

bool r(int i, int j, int v) {
  if (j - i + 1 == T.size()) {
    return (S.substr(i, j - i + 1) != T) ^ v;
  }
  if (d[i][j][v] != -1) return d[i][j][v];

  bool r1 = r(i + 1, j, 1 - v), r2 = r(i, j - 1, 1 - v);
  return d[i][j][v] = !r1 || !r2;
}

void solve() {
  cin >> S >> T;

  memset(d, -1, sizeof(d));
  if (r(0, S.size() - 1, 0)) cout << "Bob\n";
  else cout << "Alice\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
