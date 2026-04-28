#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

void solve() {
  int n, m;
  cin >> n >> m;

  int left = 0;
  for (int i = 0; i < n; i++) cin >> a[i], left = max(left, a[i]);

  int right = 1e9 + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    int cnt = 1, sum = 0;
    for (int i = 0; i < n; i++) {
      if (sum + a[i] > mid) cnt++, sum = a[i];
      else sum += a[i];
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
