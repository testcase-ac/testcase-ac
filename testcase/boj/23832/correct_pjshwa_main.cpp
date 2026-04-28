#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll phi(ll n) {
  ll result = n;
  for (ll i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0) n /= i;
      result -= result / i;
    }
  }
  if (n > 1) result -= result / n;
  return result;
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n;
  cin >> n;

  ll ans = 0;
  for (int i = 2; i <= n; i++) ans += phi(i);
  cout << ans << '\n';
}
