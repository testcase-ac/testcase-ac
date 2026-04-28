#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
int dp[MAXN + 10];
char S[MAXN + 10];

void solve() {
  int N; cin >> N >> (S + 1);

  memset(dp, 0x3f, sizeof(dp)); dp[0] = 0;
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= 3; ++j) {
      if (i - j < 0) break;

      string sub = "";
      for (int k = i - j + 1; k <= i; ++k) sub += S[k];
      if (sub[0] == '0') continue;

      int subi = stoi(sub);
      if (subi > 641) continue;

      dp[i] = min(dp[i], dp[i - j] + 1);
    }
  }

  cout << dp[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
