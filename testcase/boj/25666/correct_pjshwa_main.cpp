#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MOD = 998244353;
int a[MAX];

void solve() {
  int n;
  cin >> n;

  int p = 1;
  for (int i = 0; i < n; ++i) cin >> a[i], p *= a[i];

  int last = 0;
  for (int i = 1; i <= p; i++) {
    for (int j = 0; j < n; j++) {
      if (i % a[j] == 0) {
        cout << i - last << ' ';
        last = i;
        break;
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
