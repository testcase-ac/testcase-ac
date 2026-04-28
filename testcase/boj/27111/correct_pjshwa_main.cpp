#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  map<int, int> T;
  int ans = 0;
  for (int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;

    if (b) {
      if (T[a] == 0) T[a] = 1;
      else ans++;
    }
    else {
      if (T[a] == 0) ans++;
      else T[a] = 0;
    }
  }

  for (auto [_, v] : T) ans += v;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
