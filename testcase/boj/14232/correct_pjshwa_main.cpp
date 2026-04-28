#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  ll n;
  cin >> n;
  vector<ll> pd;
  for (ll i = 2; i * i <= n; i++) {
    while (n % i == 0) {
      pd.push_back(i);
      n /= i;
    }
  }
  if (n > 1) pd.push_back(n);

  cout << pd.size() << '\n';
  for (auto &i : pd) cout << i << ' ';
}
