#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  queue<pair<string, int>> Q;
  for (int i = 0; i < N; ++i) {
    string s; int x; cin >> s >> x;
    Q.push({s, x});
  }

  while (Q.size() > 1) {
    auto [fs, fx] = Q.front(); Q.pop();

    for (int i = 0; i < fx - 1; ++i) {
      auto [ss, sx] = Q.front(); Q.pop();
      Q.push({ss, sx});
    }
    Q.pop();
  }

  cout << Q.front().first << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
