#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200;
char board[MAX + 1][MAX + 1];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int n;
  cin >> n;
  for (int i = 0; i < 2 * n; i++) cin >> board[i];

  int w[4] = {0};
  for (int i = 0; i < 2 * n; i++) for (int j = 0; j < 2 * n; j++) {
    if (board[i][j] == 'O') continue;

    int wi = (i / n) * 2 + (j / n);
    w[wi]++;
  }

  cout << abs(w[0] - w[3]) + abs(w[1] - w[2]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
