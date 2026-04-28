#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll n_from_k(ll k) {
  ll base = 1;
  ll ans = 0;
  while (base <= k) {
    ans += (k / base);
    base *= 5;
  }
  return ans;
}

int main() {
  fast_io();

  ll n;
  cin >> n;

  ll left = 1;
  ll right = 1e8;
  ll mid = (left + right) / 2;

  while (left < right) {
    ll cn = n_from_k(mid);
    if (cn < n) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }

  if (n == n_from_k(mid)) cout << 5 * mid;
  else cout << -1;
  cout << '\n';
}
