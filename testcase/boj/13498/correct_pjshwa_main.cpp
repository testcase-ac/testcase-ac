#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, k;
  cin >> n;

  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  cin >> k;

  if (k == 1) return cout << *max_element(a.begin(), a.end()) << '\n', void();

  int left = 0, right = 1e9 + 1;
  while (left < right) {
    int mid = (left + right) / 2;

    ll cnt = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] <= mid) continue;

      cnt += (a[i] - mid - 1) / (k - 1) + 1;
    }

    if (cnt <= mid) right = mid;
    else left = mid + 1;
  }

  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
