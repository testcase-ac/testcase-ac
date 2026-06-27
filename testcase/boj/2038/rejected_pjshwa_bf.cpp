#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int dp[2000001];

int g(int n) {
  if (n == 1) return 1;

  if (dp[n] == -1) dp[n] = 1 + g(n - g(g(n - 1)));
  return dp[n];
}

int main() {
  memset(dp, -1, sizeof(dp));
  
  int n;
  cin >> n;
  cout << g(n);

}
