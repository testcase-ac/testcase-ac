#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
char board[MAX + 1][MAX + 1];
bool a[MAX][MAX];
int n;

void flip_row(int i) {
  for (int j = 0; j < n; j++) a[i][j] ^= 1;
}

void flip_col(int j) {
  for (int i = 0; i < n; i++) a[i][j] ^= 1;
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> board[i];
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) a[i][j] = board[i][j] == 'R';

  for (int j = 0; j < n; j++) if (a[n - 1][j]) flip_col(j);
  for (int i = 0; i < n; i++) if (a[i][n - 1]) flip_row(i);

  int cnt = 0, ci, cj;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    cnt += a[i][j];
    if (a[i][j]) ci = i, cj = j;
  }

  if (cnt == 1) cout << ci + 1 << ' ' << cj + 1 << '\n';
  else if (cnt == n - 1) {
    for (int i = 0; i < n; i++) {
      int rcnt = 0;
      for (int j = 0; j < n; j++) rcnt += a[i][j];
      if (rcnt == n - 1) return cout << i + 1 << " 1\n", void();
    }

    for (int j = 0; j < n; j++) {
      int ccnt = 0;
      for (int i = 0; i < n; i++) ccnt += a[i][j];
      if (ccnt == n - 1) return cout << "1 " << j + 1 << '\n', void();
    }
  }
  else if (cnt == (n - 1) * (n - 1)) cout << "1 1\n";
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
