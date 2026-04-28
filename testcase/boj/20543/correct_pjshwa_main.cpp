#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll board[2001][2001];
int main() {
  fast_io();

  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) cin >> board[i][j];
  }

  for (int j = m + 1; j <= n; j++) {
    for (int i = 1; i <= n; i++) board[i][j] += board[i][j - m];
  }

  for (int i = m + 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) board[i][j] += board[i - m][j];
  }

  for (int i = 0; i < m / 2; i++) {
    for (int j = 0; j < n; j++) cout << "0 ";
    cout << '\n';
  }
  for (int i = 1; i <= n - m + 1; i++) {
    for (int j = 0; j < m / 2; j++) cout << "0 ";
    for (int j = 1; j <= n - m + 1; j++) cout << -(board[i][j] - board[i - 1][j] - board[i][j - 1] + board[i - 1][j - 1]) << ' ';
    for (int j = 0; j < m / 2; j++) cout << "0 ";
    cout << '\n';
  }
  for (int i = 0; i < m / 2; i++) {
    for (int j = 0; j < n; j++) cout << "0 ";
    cout << '\n';
  }
}
