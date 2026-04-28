#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int f[81][41];
int n, m;

void solve() {
  vector<int> inv(n + 1);
  for (int i = 1; i <= n; i++) cin >> inv[i];
  for (int i = 1; i <= n; i++) f[inv[i]][0] = i;

  string s;
  cin.ignore();
  getline(cin, s);

  for (int j = 0; j < 40; j++)
    for (int i = 1; i <= n; i++) f[i][j + 1] = f[f[i][j]][j];

  for (int k = 1; k <= n; k++) {
    int x = m, y = k;
    for (int i = 0; x; i++) {
      if (x & 1) y = f[y][i];
      x >>= 1;
    }
    cout << s[y - 1];
  }
  cout << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> m;
    if (n == 0 && m == 0) break;
    solve();
  }
}
