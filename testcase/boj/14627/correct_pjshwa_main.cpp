#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int n, c;
int a[MAX];

bool makeable(int l) {
  ll t = 0;
  for (int i = 0; i < n; i++) t += a[i] / l;
  return t >= c;
}

void solve() {
  cin >> n >> c;
  ll s = 0;
  for (int i = 0; i < n; i++) cin >> a[i], s += a[i];

  int left = 1, right = 1e9 + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    if (makeable(mid)) left = mid + 1;
    else right = mid;
  }
  cout << s - (ll)c * (left - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
