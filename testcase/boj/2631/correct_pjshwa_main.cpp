#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();
  int n;
  cin >> n;

  int a[n];
  int dp[n];
  memset(dp, 0, sizeof(dp));

  for (int i = 0; i < n; i++) cin >> a[i];

  int max = -1;
  for (int i = 0; i < n; i++) {
    int min = 0;
    for (int j = 0; j < i; j++) {
      if (a[j] < a[i]) {
        if (min < dp[j]) min = dp[j];
      }
    }
    dp[i] = min + 1;
    if (max < dp[i]) max = dp[i];
  }
  cout << n - max << '\n';
}
