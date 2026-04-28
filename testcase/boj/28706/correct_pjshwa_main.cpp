#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
bool dp[MAXN + 1][7];

void solve() {
  int N; cin >> N;

  for (int i = 0; i <= N; ++i) fill(dp[i], dp[i] + 7, false);
  dp[0][1] = true;

  for (int i = 1; i <= N; ++i) {
    string op1, op2; int v1, v2; cin >> op1 >> v1 >> op2 >> v2;

    vector<pair<string, int>> ops = {{op1, v1}, {op2, v2}};
    for (auto& [op, v] : ops) {
      for (int pk = 0; pk < 7; ++pk) {
        int nk = (op == "+") ? pk + v : pk * v;
        nk %= 7;
        dp[i][nk] = dp[i][nk] || dp[i - 1][pk];
      }
    }
  }

  if (!dp[N][0]) cout << "UN";
  cout << "LUCKY\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
