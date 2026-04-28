#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
char board[MAX + 1][MAX + 1];
int pf[MAX + 1][MAX + 1];
int ans[10001];

void solve() {
  int n, s;
  cin >> n >> s;
  for (int i = 0; i < n; i++) cin >> board[i];

  pf[1][1] = board[0][0] == 'D';
  for (int j = 2; j <= n; j++) pf[1][j] = pf[1][j - 1] + (board[0][j - 1] == 'D');
  for (int i = 2; i <= n; i++) pf[i][1] = pf[i - 1][1] + (board[i - 1][0] == 'D');
  for (int i = 2; i <= n; i++) for (int j = 2; j <= n; j++) {
    pf[i][j] = pf[i - 1][j] + pf[i][j - 1] - pf[i - 1][j - 1] + (board[i - 1][j - 1] == 'D');
  }

  int cur = pf[s][s], last = cur;
  ans[cur]++;

  for (int j = 2; j + s - 1 <= n; j++) {
    cur -= (pf[s][j - 1] - pf[s][j - 2] - pf[0][j - 1] + pf[0][j - 2]);
    cur += (pf[s][j + s - 1] - pf[s][j + s - 2] - pf[0][j + s - 1] + pf[0][j + s - 2]);
    ans[cur]++;
  }

  for (int i = 2; i + s - 1 <= n; i++) {
    cur = last;
    cur -= (pf[i - 1][s] - pf[i - 2][s] - pf[i - 1][0] + pf[i - 2][0]);
    cur += (pf[i + s - 1][s] - pf[i + s - 2][s] - pf[i + s - 1][0] + pf[i + s - 2][0]);
    ans[cur]++;
    last = cur;

    for (int j = 2; j + s - 1 <= n; j++) {
      cur -= (pf[i + s - 1][j - 1] - pf[i + s - 1][j - 2] - pf[i - 1][j - 1] + pf[i - 1][j - 2]);
      cur += (pf[i + s - 1][j + s - 1] - pf[i + s - 1][j + s - 2] - pf[i - 1][j + s - 1] + pf[i - 1][j + s - 2]);
      ans[cur]++;
    }
  }

  for (int i = 0; i <= s * s; i++) {
    if (ans[i]) cout << i << ' ' << ans[i] << '\n';
  }
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
