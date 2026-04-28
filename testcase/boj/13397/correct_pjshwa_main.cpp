#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
int a[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  
  int left = 0, right = 1e5;
  while (left < right) {
    int mid = (left + right) / 2;

    int cnt = 1, cmin = a[1], cmax = a[1];
    for (int i = 2; i <= n; i++) {
      if (abs(a[i] - cmin) > mid || abs(a[i] - cmax) > mid) {
        cnt++;
        cmin = cmax = a[i];
      }
      else {
        cmax = max(cmax, a[i]);
        cmin = min(cmin, a[i]);
      }
    }

    if (cnt <= m) right = mid;
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
