#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
 
void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5 + 20;
int a[MAX];

void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) cin >> a[i];

  ll s = 0;
  for (int i = 0; i < n; i++) {
    s += a[i] * a[(i + 1) % n] * a[(i + 2) % n] * a[(i + 3) % n];
  }

  while (q--) {
    int x;
    cin >> x;
    x--;

    for (int i = x - 3; i <= x; i++) {
      s -= 2 * a[(i + n) % n] * a[(i + n + 1) % n] * a[(i + n + 2) % n] * a[(i + n + 3) % n];
    }
    cout << s << '\n';
    a[x] = -a[x];
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
