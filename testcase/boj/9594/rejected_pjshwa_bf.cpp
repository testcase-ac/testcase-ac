#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll N;
void solve() {
  bool f = true;
  int ans = 1;
  for (int i = 1; i <= N; i++) {
    int c = i;
    while (c % 5 == 0) {
      c /= 5;
      f = !f;
    }
    if (f) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == -1) break;
    solve();
  }
}
