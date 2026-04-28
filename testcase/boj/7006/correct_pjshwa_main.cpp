#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50;
int A[MAX + 10];
bool L[MAX + 10];
ld dp[MAX + 10][MAX + 10];
int m, T;

ld r(int i, int t) {
  if (i == m + 1) return 1.0;
  if (t >= T) return 0.0;
  if (dp[i][t] != -1) return dp[i][t];

  ld ret = 0.0;
  for (int nxt : {i + 1, i + 2}) {
    nxt = min(nxt, m + 1);

    if (L[nxt]) ret += 0.5 * r(nxt, t + 2);
    else ret += 0.5 * r(nxt + A[nxt], t + 1);
  }

  return dp[i][t] = ret;
}

void solve() {
  cin >> m >> T;

  memset(A, 0, sizeof(A));
  memset(L, 0, sizeof(L));

  for (int i = 1; i <= m; ++i) {
    string o; cin >> o;
    if (o == "L") L[i] = 1;
    else A[i] = stoi(o);
  }
  for (int i = 0; i <= m + 1; ++i) for (int j = 0; j <= T; ++j) dp[i][j] = -1;

  ld ans = r(0, 0);
  if (ans > 0.5) cout << "Bet for. ";
  else if (ans < 0.5) cout << "Bet against. ";
  else cout << "Push. ";

  cout << fixed << setprecision(4) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
