#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int M; cin >> M;

  map<int, int> L_by_wgt;
  while (M--) {
    int op; cin >> op;
    if (op == 1) {
      int x, w; cin >> x >> w;
      L_by_wgt[w] = x;
    }
    else {
      int w; cin >> w;
      cout << L_by_wgt[w] << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
