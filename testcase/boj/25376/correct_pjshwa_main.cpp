#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20, INF = 1e9 + 7;
int B[MAX];
int cdist[1 << MAX];

void solve() {
  int N;
  cin >> N;

  int s = 0;
  for (int i = 0, x; i < N; i++) {
    cin >> x;
    if (x) s |= (1 << i);
  }
  for (int i = 0, z; i < N; i++) {
    cin >> z;
    for (int j = 0, x; j < z; j++) {
      cin >> x;
      B[i] |= (1 << (x - 1));
    }
  }

  fill(cdist, cdist + (1 << N), INF);
  queue<pii> q;
  q.push({s, 0});
  cdist[s] = 0;

  while (!q.empty()) {
    auto [v, c] = q.front();
    q.pop();

    for (int i = 0; i < N; i++) {
      if (v & (1 << i)) continue;
      int nv = v | (1 << i);
      nv ^= B[i];
      if (c + 1 < cdist[nv]) {
        cdist[nv] = c + 1;
        q.push({nv, c + 1});
      }
    }
  }

  if (cdist[(1 << N) - 1] == INF) cout << "-1\n";
  else cout << cdist[(1 << N) - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
