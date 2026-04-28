#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1 << 20;
bool vis[MAX];

void solve() {
  int n, q;
  cin >> n >> q;
  while (q--) {
    int x, o;
    cin >> x, o = x;

    bool found = 0;
    int fx;
    while (x) {
      if (vis[x]) found = 1, fx = x;
      x /= 2;
    }

    if (found) cout << fx << '\n';
    else vis[o] = 1, cout << "0\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
