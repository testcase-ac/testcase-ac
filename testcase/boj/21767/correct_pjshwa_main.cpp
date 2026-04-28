#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 20;
int C[MAX], cdist[1 << MAX];

void solve() {
  int N, K, M; cin >> N >> K >> M;
  for (int i = 0; i < N; i++) cin >> C[i];

  vector<int> P(M);
  for (int i = 0; i < M; i++) {
    int r, x; cin >> r;
    while (r--) {
      cin >> x;
      P[i] |= 1 << (x - 1);
    }
  }

  int S = 0;
  for (int i = 0; i < N; i++) if (C[i] == 1) S |= 1 << i;

  memset(cdist, -1, sizeof(cdist));
  queue<int> q;
  q.push(S); cdist[S] = 0;

  while (!q.empty()) {
    int s = q.front(); q.pop();

    int cov = 0;
    for (int j = 0; j < M; j++) {
      if (s & (1 << (N + j))) cov |= P[j];
    }

    // 1. Immerse the ball
    for (int c = 1; c <= K; c++) {
      int ns = s;
      for (int i = 0; i < N; i++) {
        if (cov & (1 << i)) continue;

        if (C[i] == c) ns |= 1 << i;
        else ns &= ~(1 << i);
      }

      if (cdist[ns] != -1) continue;
      cdist[ns] = cdist[s] + 1;
      q.push(ns);
    }

    // 2. Equip one equipment
    for (int j = 0; j < M; j++) {
      if (s & (1 << (N + j))) continue;

      int ns = s | (1 << (N + j));
      if (cdist[ns] != -1) continue;
      cdist[ns] = cdist[s] + 1;
      q.push(ns);
    }

    // 3. Unequip one equipment
    for (int j = 0; j < M; j++) {
      if (!(s & (1 << (N + j)))) continue;

      int ns = s & ~(1 << (N + j));
      if (cdist[ns] != -1) continue;
      cdist[ns] = cdist[s] + 1;
      q.push(ns);
    }
  }

  cout << cdist[(1 << N) - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
