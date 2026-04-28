#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<ll> U;

bool is_prime(ll n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (ll i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

void dfs(ll pre) {
  U.push_back(pre);

  for (int e = 1; e <= 9; e += 2) {
    if (is_prime(10 * pre + e)) dfs(10 * pre + e);
  }
}

int main() {
  fast_io();

  for (int e : {2, 3, 5, 7}) dfs(e);
  sort(U.begin(), U.end());

  ll a, b;
  cin >> a >> b;

  auto it = lower_bound(U.begin(), U.end(), a);
  auto jt = upper_bound(U.begin(), U.end(), b);
  cout << jt - it << '\n';

}
