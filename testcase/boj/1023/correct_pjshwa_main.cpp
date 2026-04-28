#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll dp[51][120][2];
const int bias = 51;

ll invalid_pcnt(int n, int fw, bool v) {
  if (n == 0) return !(fw == 0 && v);
  if (dp[n][fw + bias][v] != -1) return dp[n][fw + bias][v];

  ll ans = invalid_pcnt(n - 1, fw + 1, v);
  ans += invalid_pcnt(n - 1, fw - 1, v && fw > 0);
  return dp[n][fw + bias][v] = ans;
}

string kth_invalid(int n, ll k) {
  string ans = "";
  int fw = 0;
  bool v = true;

  while (n) {
    ll thresh = invalid_pcnt(n - 1, fw + 1, v);
    if (k <= thresh) {
      ans += '(';
      fw++;
    }
    else {
      ans += ')';
      fw--;
      k -= thresh;
      if (fw < 0) v = false;
    }
    n--;
  }
  return ans;
}

int main() {
  fast_io();

  ll n, k;
  cin >> n >> k;
  k++;

  memset(dp, -1, sizeof(dp));
  ll sz = invalid_pcnt(n, 0, true);
  if (k > sz) cout << -1;
  else cout << kth_invalid(n, k);
}
