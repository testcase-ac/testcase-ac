#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
pair<string, string> ops[MAX + 1];
int d[2][MAX + 1];

int apply(string op, int u) {
  if (op[0] == '+') return u + (op[1] - '0');
  if (op[0] == '-') return u - (op[1] - '0');
  if (op[0] == '*') return u * (op[1] - '0');
  if (op[0] == '/') return u / (op[1] - '0');
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> ops[i].first >> ops[i].second;

  d[0][0] = d[1][0] = 1;
  for (int i = 1; i <= n; i++) {
    if (d[0][i - 1] == -1) d[0][i] = -1;
    else d[0][i] = max(apply(ops[i].first, d[0][i - 1]), apply(ops[i].second, d[0][i - 1]));
    if (d[0][i] <= 0) d[0][i] = -1;

    if (d[1][i - 1] == -1) d[1][i] = -1;
    else d[1][i] = max(apply(ops[i].first, d[1][i - 1]), apply(ops[i].second, d[1][i - 1]));
    d[1][i] = max(d[1][i], d[0][i - 1]);
    if (d[1][i] <= 0) d[1][i] = -1;
  }

  int ans = max(d[0][n], d[1][n]);
  if (ans == -1) cout << "ddong game\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
