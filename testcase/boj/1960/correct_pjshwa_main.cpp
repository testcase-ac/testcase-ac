#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
int R[MAXN], C[MAXN], Rv[MAXN], Cv[MAXN], B[MAXN][MAXN];

void solve() {
  int N, sum = 0; cin >> N;
  for (int i = 0; i < N; ++i) cin >> R[i], sum += R[i];

  priority_queue<pii> pq;
  for (int i = 0; i < N; ++i) {
    cin >> C[i];
    sum -= C[i];
    pq.emplace(C[i], i);
  }
  if (sum != 0) return cout << "-1\n", void();

  queue<pii> wait;
  for (int i = 0; i < N; ++i) {
    int r = R[i];
    if (r > N) return cout << "-1\n", void();
    while (r--) {
      auto [c, j] = pq.top(); pq.pop();
      B[i][j] = 1;
      if (c) wait.emplace(c - 1, j);
    }
    while (!wait.empty()) {
      pq.push(wait.front()); wait.pop();
    }
  }

  // verify
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    Rv[i] += B[i][j];
    Cv[j] += B[i][j];
  }
  for (int i = 0; i < N; ++i) {
    if (Rv[i] != R[i]) return cout << "-1\n", void();
    if (Cv[i] != C[i]) return cout << "-1\n", void();
  }

  cout << "1\n";
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cout << B[i][j];
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
