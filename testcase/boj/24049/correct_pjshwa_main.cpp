#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int g[MAX][MAX];
int a[MAX], b[MAX];
int n, m;

void print_board() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << g[i][j] << " ";
    }
    cout << endl;
  }
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int j = 0; j < m; j++) cin >> b[j];

  g[0][0] = (a[0] + b[0]) % 2;
  for (int i = 1; i < n; i++) g[i][0] = (g[i - 1][0] + a[i]) % 2;
  for (int j = 1; j < m; j++) g[0][j] = (g[0][j - 1] + b[j]) % 2;
  for (int i = 1; i < n; i++) for (int j = 1; j < m; j++) {
    g[i][j] = (g[i - 1][j] + g[i][j - 1]) % 2;
  }

  // print_board();
  cout << g[n - 1][m - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
