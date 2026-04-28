#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXP = 2e4;
int T[MAXP + 1];

void solve() {
  int N, P = 10000; cin >> N;
  for (int i = 0; i < N; ++i) {
    int p, x, f; cin >> p >> x >> f;
    if (f == 1) {
      int sell = max(-T[p], 0);
      int b = min(sell, x);
      if (b > 0) P = p;
      T[p] += x;
    }
    else {
      int buy = max(T[p], 0);
      int s = min(buy, x);
      if (s > 0) P = p;
      T[p] -= x;
    }
  }

  cout << P << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
