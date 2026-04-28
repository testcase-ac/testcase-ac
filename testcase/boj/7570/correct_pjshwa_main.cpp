#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 1e6 + 1;
int dp[MAX];
int main() {
  fast_io();

  int n, a, mx = 0;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> a;
    dp[a] = dp[a - 1] + 1;
    mx = max(mx, dp[a]);
  }

  cout << n - mx << '\n';
}
