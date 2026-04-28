#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 1e9 + 7;
int OP[MAX + 1][MAX + 1], P[MAX + 1][MAX + 1];
int N;

int f(int i) {
  int t[4][4] = {0};
  for (int j = 1; j <= i; j++) t[OP[i][j]][P[i][j]]++;

  int res = 0;
  while (t[1][2] && t[2][1]) res++, t[1][2]--, t[2][1]--;
  while (t[1][3] && t[3][1]) res++, t[1][3]--, t[3][1]--;
  while (t[2][3] && t[3][2]) res++, t[2][3]--, t[3][2]--;
  while (t[1][2] && t[2][3] && t[3][1]) res += 2, t[1][2]--, t[2][3]--, t[3][1]--;
  while (t[1][3] && t[3][2] && t[2][1]) res += 2, t[1][3]--, t[3][2]--, t[2][1]--;

  return res;
}

bool valid() {
  if (OP[1][1] == OP[2][1]) return false;
  if (OP[1][1] == OP[2][2]) return false;
  if (OP[2][1] == OP[2][2]) return false;

  for (int i = 1; i <= N; i++) {
    if (i <= 2) {
      for (int j = 1; j <= i; j++) P[i][j] = OP[i][j];
      continue;
    }

    for (int j = 2; j <= i - 1; j++) P[i][j] = P[i - 1][j - 1] ^ P[i - 1][j];
    P[i][1] = P[i - 1][1] ^ P[i][2];
    P[i][i] = P[i - 1][i - 1] ^ P[i][i - 1];
  }

  for (int i = 1; i <= N; i++) {
    int t[4] = {0};
    for (int j = 1; j <= i; j++) t[OP[i][j]]++, t[P[i][j]]--;
    if (t[1] != 0 || t[2] != 0 || t[3] != 0) return false;
  }

  return true;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= i; j++) cin >> OP[i][j], OP[i][j]++;
  if (N == 1) return cout << "0\n", void();

  if (!valid()) return cout << "-1\n", void();

  int ans = INF, cur;

  // Keep 2nd row
  cur = 0;
  P[2][1] = OP[2][1], P[2][2] = OP[2][2];
  for (int i = 3; i <= N; i++) {
    // Fill target
    for (int j = 2; j <= i - 1; j++) P[i][j] = P[i - 1][j - 1] ^ P[i - 1][j];
    P[i][1] = P[i - 1][1] ^ P[i][2];
    P[i][i] = P[i - 1][i - 1] ^ P[i][i - 1];

    cur += f(i);
  }
  ans = min(ans, cur);

  // Swap 2nd row
  cur = 1;
  P[2][1] = OP[2][2], P[2][2] = OP[2][1];
  for (int i = 3; i <= N; i++) {
    for (int j = 2; j <= i - 1; j++) P[i][j] = P[i - 1][j - 1] ^ P[i - 1][j];
    P[i][1] = P[i - 1][1] ^ P[i][2];
    P[i][i] = P[i - 1][i - 1] ^ P[i][i - 1];

    cur += f(i);
  }
  ans = min(ans, cur);

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
