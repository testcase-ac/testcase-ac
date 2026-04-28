#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[100], v[100];
ll dp[10005];
int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];

  int totv = 0;
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    totv += v[i];
  }

  for (int i = 0; i < n; i++) {
    for (int j = totv; j >= v[i]; j--) dp[j] = max(dp[j], dp[j - v[i]] + a[i]);
  }

  for (int j = 0; j <= totv; j++) {
    if (dp[j] >= m) {
      cout << j;
      break;
    }
  }
}
