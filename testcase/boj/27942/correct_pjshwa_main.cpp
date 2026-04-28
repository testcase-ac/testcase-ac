#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
ll A[MAX + 5][MAX + 5], P[MAX + 5][MAX + 5];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) cin >> A[i][j];
  for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
    P[i][j] = A[i][j] + P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1];
  }

  int si = N / 2, sj = N / 2;
  int ei = si + 1, ej = sj + 1;

  ll ans = 0;
  vector<char> dirs;
  while (1) {
    char d; ll add = 0;

    for (char c : {'U', 'D', 'L', 'R'}) {
      ll cur = 0;
      if (c == 'U' && si > 1) {
        cur = P[si - 1][ej] - P[si - 1][sj - 1] - P[si - 2][ej] + P[si - 2][sj - 1];
      }
      if (c == 'D' && ei < N) {
        cur = P[ei + 1][ej] - P[ei + 1][sj - 1] - P[ei][ej] + P[ei][sj - 1];
      }
      if (c == 'L' && sj > 1) {
        cur = P[ei][sj - 1] - P[si - 1][sj - 1] - P[ei][sj - 2] + P[si - 1][sj - 2];
      }
      if (c == 'R' && ej < N) {
        cur = P[ei][ej + 1] - P[si - 1][ej + 1] - P[ei][ej] + P[si - 1][ej];
      }
      if (add < cur) {
        add = cur;
        d = c;
      }
    }

    if (add <= 0) break;

    ans += add;
    dirs.push_back(d);
    if (d == 'U') si--;
    if (d == 'D') ei++;
    if (d == 'L') sj--;
    if (d == 'R') ej++;
  }

  cout << ans << '\n';
  for (char c : dirs) cout << c;
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
