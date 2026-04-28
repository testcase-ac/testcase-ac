#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int d[MAX + 1];

void solve() {
  int N, K; cin >> N >> K;
  cout << (d[N] <= K ? "minigimbob" : "water") << '\n';
}

int main() {
  fast_io();

  memset(d, 0x3f, sizeof(d)); d[0] = 0;
  for (int i = 0; i <= MAX; i++) {
    int nxt1 = i + 1, nxt2 = i + (i / 2);
    for (int nxt : {nxt1, nxt2}) {
      if (nxt <= MAX) d[nxt] = min(d[nxt], d[i] + 1);
    }
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
