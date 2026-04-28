#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2500;
bitset<MAX + 1> t;

void solve(int tc) {
  cout << "Case #" << tc << ": ";

  int n;
  cin >> n;

  t.reset();

  for (int i = 0; i < 2 * n - 1; i++) for (int j = 0; j < n; j++) {
    int x;
    cin >> x;
    t.flip(x);
  }

  for (int i = 1; i <= MAX; i++) if (t[i]) {
    cout << i << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  for (int tc = 1; tc <= t; tc++) solve(tc);
}
