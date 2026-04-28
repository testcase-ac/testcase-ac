#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int a[MAX], k;

void swap_track(int i, int j) {
  swap(a[i], a[j]);
  if (!--k) {
    cout << min(a[i], a[j]) << ' ' << max(a[i], a[j]) << '\n';
    exit(0);
  }
}

void solve() {
  int n, q;
  cin >> n >> q >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  int left = 0, right = n - 1;
  while (1) {
    if (left == right) break;

    int x = a[right], i = left - 1;
    for (int j = left; j < right; j++) {
      if (a[j] <= x) swap_track(++i, j);
    }
    if (i + 1 != right) swap_track(i + 1, right);

    int t = i + 1, k = t - left + 1;
    if (q < k) right = t - 1;
    else if (q == k) break;
    else {
      q -= k;
      left = t + 1;
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
