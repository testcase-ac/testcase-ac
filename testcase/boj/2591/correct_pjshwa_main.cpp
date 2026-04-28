#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int dp[200];
int main() {
  fast_io();

  string s;
  cin >> s;
  int n = s.size();

  dp[0] = 1;
  for (int i = 0; i < n - 1; i++) {
    if (s[i] == '0') continue;

    if (s[i + 1] != '0') dp[i + 1] += dp[i];
    if (
      ((s[i] == '1' || s[i] == '2') || (s[i] == '3' && s[i + 1] <= '4'))
    ) dp[i + 2] += dp[i];
  }

  if (s[n - 1] != '0') dp[n] += dp[n - 1];
  cout << dp[n];
}
