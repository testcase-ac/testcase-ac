#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, t; cin >> N >> t;

  int k = N / 2;
  if (t) k++;
  cout << "! " << k << endl;

  int it = 0;
  if (t) {
    cout << "1 1" << endl;
    t = 0; it++;
  }

  int a, b;
  while (it < N) {
    if (t == 0) cin >> a >> b;
    if (t == 1) cout << b << ' ' << a << endl;
    t = 1 - t; it++;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
