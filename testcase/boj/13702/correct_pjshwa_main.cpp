#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int a[MAX];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  ll left = 1, right = 1LL << 31;
  while (left < right) {
    ll mid = (left + right) / 2;
    ll cnt = 0;
    for (int i = 0; i < n; i++) cnt += a[i] / mid;

    if (cnt < k) right = mid;
    else left = mid + 1;
  }

  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
