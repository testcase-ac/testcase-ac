#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, v = 0; cin >> N;
  set<int> U; U.insert(0);
  for (int i = 1; i <= N; ++i) {
    int nxt = v - i;
    if (nxt < 0 || U.count(nxt)) nxt = v + i;
    U.insert(nxt); v = nxt;
  }
  cout << v << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
