#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int D[MAX + 5], cdist[MAX + 5];

void solve() {
  int N, M, A, B; cin >> N >> M >> A >> B;

  while (M--) {
    int L, R; cin >> L >> R;
    D[L]++, D[R + 1]--;
  }
  for (int i = 1; i <= N; i++) D[i] += D[i - 1];

  memset(cdist, -1, sizeof(cdist));

  queue<int> q;
  q.push(0); cdist[0] = 0;

  while (!q.empty()) {
    int cur = q.front(); q.pop();
    
    for (int add : {A, B}) {
      int nxt = cur + add;
      if (nxt > N || D[nxt] || cdist[nxt] != -1) continue;
      cdist[nxt] = cdist[cur] + 1;
      q.push(nxt);
    }
  }

  cout << cdist[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
