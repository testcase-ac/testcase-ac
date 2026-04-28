#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 7500, MOD = 2019201997;
int mreach[MAX + 1], used[MAX + 1];

int dist(int x, int y) {
  if (x > y) swap(x, y);
  return (2019201913LL * x + 2019201949LL * y) % MOD;
}

void solve() {
  int N, K;
  cin >> N >> K;

  // Modified Prim's algorithm
  fill(mreach + 1, mreach + N + 1, MOD);

  for (int i = 0; i < N; i++) {
    int wgt = mreach[1], sv = 1;
    for (int j = 1; j <= N; j++) { 
      if (!used[j] && mreach[j] < wgt) sv = j, wgt = mreach[j];
    }

    used[sv] = 1;
    for (int to = 1; to <= N; to++) {
      if (!used[to]) mreach[to] = min(mreach[to], dist(sv, to));
    }
  }

  sort(mreach + 1, mreach + N + 1);
  cout << mreach[N - K + 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
