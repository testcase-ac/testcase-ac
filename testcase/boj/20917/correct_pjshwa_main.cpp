#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int a[MAX];
int n, k;

bool feasible(int d) {
  int v = a[0];
  for (int i = 0; i < k - 1; i++) {
    auto it = lower_bound(a, a + n, v + d);
    if (it == a + n) return false;
    v = *it;
  }
  return true;
}

void solve() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  int left = 1, right = 1e9 + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    if (feasible(mid)) left = mid + 1;
    else right = mid;
  }

  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
