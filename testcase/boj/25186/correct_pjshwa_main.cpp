#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
ll a[MAX];

void solve() {
  int n;
  cin >> n;

  ll sum = 0;
  for (int i = 0; i < n; i++) cin >> a[i], sum += a[i];

  if (n == 1 && a[0] == 1) return cout << "Happy\n", void();

  for (int i = 0; i < n; i++) {
    if (a[i] * 2 > sum) return cout << "Unhappy\n", void();
  }

  cout << "Happy\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
