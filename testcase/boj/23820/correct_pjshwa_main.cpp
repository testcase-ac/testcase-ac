#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e6 + 3;
bool c[MAX + 1], t[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    t[x] = true;
  }

  if (t[0]) c[0] = true;
  for (int i = 1; i <= MAX; i++) {
    for (int j = 1; j * i <= MAX; j++) {
      if (t[i] && t[j]) c[i * j] = true;
    }
  }

  for (int i = 0; i <= MAX; i++) {
    if (!c[i]) return cout << i << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
