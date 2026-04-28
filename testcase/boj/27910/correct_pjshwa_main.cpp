#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, q; cin >> n >> q;
  while (q--) {
    int x; cin >> x;
    if (x == 1) {
      cout << "-1\n";
      continue;
    }

    vector<int> fs; int ox = x;
    for (int f = 2; f * f <= ox; f++) {
      if (x % f == 0) {
        fs.push_back(f);
        while (x % f == 0) x /= f;
      }
    }
    if (x > 1) fs.push_back(x);

    int y = fs.back();
    cout << n / y - 1 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
