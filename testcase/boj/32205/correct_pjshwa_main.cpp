#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e6;
int P[MAXV + 1];

void solve() {
  int N, x; cin >> N;
  for (int i = 0; i < 3 * N; ++i) {
    cin >> x;
    if (P[x]) return cout << "1\n", void();
    P[x] = 1;
  }
  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
