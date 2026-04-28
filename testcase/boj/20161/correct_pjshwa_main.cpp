#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
int A[MAX], cdist[MAX + 1][1 << 10];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0, x; i < N; ++i) cin >> x, A[i] ^= x;
  int mask = (1 << K) - 1;

  memset(cdist, 0x3f, sizeof(cdist));
  deque<pii> dq;
  dq.push_front({K - 1, 0});
  cdist[K - 1][0] = 0;

  while (!dq.empty()) {
    auto [i, s] = dq.front(); dq.pop_front();
    if (i == N) continue;

    // move 1 forward if constraint is satisfied
    int ns = (s >> 1);
    if (i < N && A[i - K + 1] == (s & 1) && cdist[i + 1][ns] > cdist[i][s]) {
      cdist[i + 1][ns] = cdist[i][s];
      dq.push_front({i + 1, ns});
    }

    // stay at the spot, do another flip
    for (int j = 0; j < K; ++j) {
      int ns = s ^ mask ^ (1 << j);
      if (cdist[i][ns] > cdist[i][s] + 1) {
        cdist[i][ns] = cdist[i][s] + 1;
        dq.push_back({i, ns});
      }
    }
  }

  int rstate = 0;
  for (int j = 0; j < K; ++j) rstate |= (A[N - K + j] << j);
  int ans = cdist[N - 1][rstate];

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
