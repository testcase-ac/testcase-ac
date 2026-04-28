#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n;
  cin >> n;

  int p[n];
  for (int i = 0; i < n; i++) p[i] = i + 1;

  do {
    bool f = true;
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) for (int k = j + 1; k < n; k++) {
      if (p[i] + p[k] == 2 * p[j]) f = false;
    }
    if (f) {
      for (int i = 0; i < n; i++) cout << p[i] << ' ';
      cout << '\n';
    }

  } while (next_permutation(p, p + n));
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
