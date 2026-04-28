#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, oc = 0, x;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> x;
    if (x & 1) oc++;
  }

  if (N & 1) {
    if (oc == (N + 1) / 2) cout << "1\n";
    else cout << "0\n";
  }
  else {
    if (oc == N / 2) cout << "1\n";
    else cout << "0\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
