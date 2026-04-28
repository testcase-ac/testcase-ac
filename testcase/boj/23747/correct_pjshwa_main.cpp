#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
char board[MAX + 1][MAX + 1];
int parent[MAX * MAX + 1];

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
  for (int i = 0; i < n; i++) cin >> board[i];
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) parent[i * m + j] = i * m + j;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (j < m - 1 && board[i][j] == board[i][j + 1]) {
      Union(i * m + j, i * m + j + 1);
    }
    if (i < n - 1 && board[i][j] == board[i + 1][j]) {
      Union(i * m + j, (i + 1) * m + j);
    }
  }

  int ci, cj;
  string moves;
  cin >> ci >> cj >> moves;
  ci--; cj--;

  set<int> wards;
  for (char move : moves) {
    if (move == 'L') cj--;
    if (move == 'R') cj++;
    if (move == 'U') ci--;
    if (move == 'D') ci++;
    if (move == 'W') wards.insert(Find(ci * m + cj));
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (abs(ci - i) <= 1 && cj == j) cout << '.';
      else if (abs(cj - j) <= 1 && ci == i) cout << '.';
      else if (wards.count(Find(i * m + j))) cout << '.';
      else cout << '#';
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
