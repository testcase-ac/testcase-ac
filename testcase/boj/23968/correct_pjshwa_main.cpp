#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int MAX = 1e5;
int a[MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int i = n - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      if (a[j] > a[j + 1]) {
        swap(a[j], a[j + 1]);
        if (!--k) return cout << a[j] << ' ' << a[j + 1] << '\n', void();
      }
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
