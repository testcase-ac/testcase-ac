#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6, MOD = 1e6;
int dp[MAX + 1];

int rec(int i) {
  if (dp[i] != -1) return dp[i];
  int ans = 0;
  if (i == 0) ans = 1;
  else {
    ans = (ans + rec(i - sqrt(i))) % MOD;
    ans = (ans + rec(log(i))) % MOD;
    ans = (ans + rec(i * sin(i) * sin(i))) % MOD;
  }
  return dp[i] = ans;
}

int main() {
  fast_io();

  memset(dp, -1, sizeof(dp));

  while (1) {
    int n;
    cin >> n;
    if (n == -1) break;
    cout << rec(n) << '\n';
  }
}
