#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
char board[MAX + 1][MAX + 1];
int pj[MAX + 1][MAX + 1], po[MAX + 1][MAX + 1], pi[MAX + 1][MAX + 1];

void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 0; i < n; i++) cin >> board[i];

  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    pj[i][j] = pj[i - 1][j] + pj[i][j - 1] - pj[i - 1][j - 1] + (board[i - 1][j - 1] == 'J');
    po[i][j] = po[i - 1][j] + po[i][j - 1] - po[i - 1][j - 1] + (board[i - 1][j - 1] == 'O');
    pi[i][j] = pi[i - 1][j] + pi[i][j - 1] - pi[i - 1][j - 1] + (board[i - 1][j - 1] == 'I');
  }

  while (q--) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a--, b--;
    cout << pj[c][d] - pj[a][d] - pj[c][b] + pj[a][b] << ' ';
    cout << po[c][d] - po[a][d] - po[c][b] + po[a][b] << ' ';
    cout << pi[c][d] - pi[a][d] - pi[c][b] + pi[a][b] << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
