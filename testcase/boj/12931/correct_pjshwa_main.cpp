#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
int o[MAX], e[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    while (x) {
      if (x & 1) o[i]++, x--;
      else e[i]++, x /= 2;
    }
  }

  cout << accumulate(o, o + n, 0) + *max_element(e, e + n) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
