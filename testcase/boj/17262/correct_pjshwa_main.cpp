#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N; cin >> N;

  int ts = INF, te = 0;
  for (int i = 0; i < N; i++) {
    int s, e; cin >> s >> e;
    ts = min(ts, e);
    te = max(te, s);
  }

  cout << max(0, te - ts) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
