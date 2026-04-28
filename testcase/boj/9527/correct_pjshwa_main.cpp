#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll lpow(ll x, ll y, ll m){
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

ll dp[55];

ll upto(ll b) {
  vector<int> vb;
  vb.resize(55);

  int i = 0;
  while (b) {
    vb[i++] = b & 1;
    b >>= 1;
  }

  ll ans = 0, k = 0;
  for (int j = i - 1; j >= 0; j--) {
    if (vb[j]) ans += (dp[j] + lpow(2, j, 1e18) * (k++));
  }

  return ans;
}

int main() {
  fast_io();

  ll k = 1;
  dp[0] = 1;
  for (int i = 1; i < 55; i++) {
    dp[i] = k * i + 1;
    k <<= 1;
  }

  ll a, b;
  cin >> a >> b;
  cout << upto(b) - upto(a - 1) << '\n';
}
