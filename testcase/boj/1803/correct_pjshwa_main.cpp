#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int indegree[MAXN + 1], P[MAXN + 1];
int U[MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; ++i) {
    int x; cin >> x;
    P[i] = x + N;
  }
  for (int i = N + 1; i <= N + M; ++i) {
    int x; cin >> x;
    P[i] = x; ++indegree[x];
  }

  fill(U + N + 1, U + N + M + 1, 1);
  queue<int> Q;
  for (int i = 1; i <= N; ++i) {
    if (indegree[i] == 0) Q.push(i);
  }

  while (!Q.empty()) {
    int i = Q.front(); Q.pop();
    U[i] = 1;

    int x = P[i];
    if (indegree[x] == 0) {
      U[x] = 0;
      if (!--indegree[P[x]]) Q.push(P[x]);
    }
    ++indegree[x];
  }

  for (int i = 1; i <= N + M; ++i) {
    cout << U[i];
    if (i == N || i == N + M) cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
