#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
int n, m;
int tc;
int inv[MAX][2500];

void solve() {
  cout << "Case " << ++tc << ": ";

  for (int i = 0; i < m; i++) {
    for (int j = 0, x; j < n; j++) {
      cin >> x;
      inv[i][x] = j;
    }
  }

  int winner = 0;
  for (int op = 1; op < n; op++) {
    int wc = 0;
    for (int i = 0; i < m; i++) {
      if (inv[i][winner] < inv[i][op]) wc++;
    }
    if (wc <= m - wc) winner = op;
  }

  for (int op = 0; op < n; op++) {
    if (op == winner) continue;

    int wc = 0;
    for (int i = 0; i < m; i++) {
      if (inv[i][winner] < inv[i][op]) wc++;
    }
    if (wc <= m - wc) return cout << "No Condorcet winner\n", void();
  }

  cout << winner << '\n';
}

int main() {
  fast_io();

  while (cin >> m >> n) {
    if (m == 0 && n == 0) break;
    solve();
  }
}
