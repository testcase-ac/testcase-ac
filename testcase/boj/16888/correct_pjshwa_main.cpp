#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool dp[(int)1e6 + 1];
int main() {
  fast_io();

  int tt, n;
  cin >> tt;

  for (int i = 1; i <= 1e3; i++) dp[i * i] = true;
  for (int i = 2; i <= 1e6; i++) {
    for (int j = 1; j * j <= i; j++) dp[i] |= !dp[i - j * j];
  }

  while (tt--) {
    cin >> n;
    cout << (dp[n] ? "koosaga" : "cubelover") << '\n';
  }
}
