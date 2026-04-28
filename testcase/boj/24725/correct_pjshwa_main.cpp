#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200;
char b[MAX + 1][MAX + 1];

bool is_mbti(char a, char b, char c, char d) {
  return (a == 'E' || a == 'I') && (b == 'N' || b == 'S') && (c == 'T' || c == 'F') && (d == 'J' || d == 'P');
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> b[i];

  int cnt = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (j + 3 < m && is_mbti(b[i][j], b[i][j + 1], b[i][j + 2], b[i][j + 3])) cnt++;
    if (i + 3 < n && is_mbti(b[i][j], b[i + 1][j], b[i + 2][j], b[i + 3][j])) cnt++;
    if (i + 3 < n && j + 3 < m && is_mbti(b[i][j], b[i + 1][j + 1], b[i + 2][j + 2], b[i + 3][j + 3])) cnt++;
    if (i + 3 < n && j - 3 >= 0 && is_mbti(b[i][j], b[i + 1][j - 1], b[i + 2][j - 2], b[i + 3][j - 3])) cnt++;
    if (j - 3 >= 0 && is_mbti(b[i][j], b[i][j - 1], b[i][j - 2], b[i][j - 3])) cnt++;
    if (i - 3 >= 0 && j - 3 >= 0 && is_mbti(b[i][j], b[i - 1][j - 1], b[i - 2][j - 2], b[i - 3][j - 3])) cnt++;
    if (i - 3 >= 0 && is_mbti(b[i][j], b[i - 1][j], b[i - 2][j], b[i - 3][j])) cnt++;
    if (i - 3 >= 0 && j + 3 < m && is_mbti(b[i][j], b[i - 1][j + 1], b[i - 2][j + 2], b[i - 3][j + 3])) cnt++;
  }

  cout << cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
