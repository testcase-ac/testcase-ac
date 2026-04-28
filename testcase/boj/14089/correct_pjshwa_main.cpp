#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  int Q; cin >> Q;
  while (Q--) {
    int p, x, q, y; cin >> p >> x >> q >> y; p--, q--;
    if (p > q) swap(p, q), swap(x, y);

    int it = q - p;
    if (p == 0) it--;

    ll xdt = x - A[p], ydt = y - A[q];
    for (int i = 0; ydt != 0 && i < it; i++) {
      if (abs(xdt) < abs(ydt)) break;
      ydt *= 2;
    }

    ll dif = xdt + ydt;
    if (dif > 0) cout << ">\n";
    else if (dif < 0) cout << "<\n";
    else cout << "=\n";

    A[p] = x, A[q] = y;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
