#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll fcount(ll k) {
  ll cnt = 0;
  for (int i = 1; i <= sqrt(k); i++) {
    if (k % i == 0) {
      cnt++;
      if (i != k / i) cnt++;
    }
  }
  return cnt;
}

ll h(ll x) {
  ll dn = fcount(x), res = 1;
  for (int i = 0; i < dn; i++) res *= x;
  return res;
}

const int MAX = 2e9;

int main() {
  fast_io();

  ll n;
  cin >> n;

  int ans = MAX;
  for (int i = 2; i <= 10; i++) {
    int base = round(pow(n, 1.0 / i));
    if (n == h(base)) ans = min(ans, base);
  }
  cout << (ans == MAX ? -1 : ans);
}
