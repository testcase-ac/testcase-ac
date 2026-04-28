#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
char board[MAX + 10][MAX + 10];
int parent[1'000'000];

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
  int n, m;
  cin >> n >> m;
  for (int i = 0; i <= n + 1; i++) for (int j = 0; j <= m + 1; j++) {
    int v = i * 1000 + j;
    parent[v] = v;
  }
  for (int i = 1; i <= n + 1; i++) Union(i * 1000, (i - 1) * 1000);
  for (int j = 1; j <= m + 1; j++) Union(j, j - 1);
  for (int j = 1; j <= m + 1; j++) Union((n + 1) * 1000 + j, (n + 1) * 1000 + j - 1);
  for (int i = 1; i <= n + 1; i++) Union(i * 1000 + m + 1, (i - 1) * 1000 + m + 1);
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    for (int j = 1; j <= m; j++) board[i][j] = s[j - 1];
  }

  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    if (board[i][j] == 'U') Union(i * 1000 + j, (i - 1) * 1000 + j);
    if (board[i][j] == 'D') Union(i * 1000 + j, (i + 1) * 1000 + j);
    if (board[i][j] == 'L') Union(i * 1000 + j, i * 1000 + j - 1);
    if (board[i][j] == 'R') Union(i * 1000 + j, i * 1000 + j + 1);
  }

  int o = Find(0), ans = 0;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    int v = i * 1000 + j;
    if (Find(v) == o) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
