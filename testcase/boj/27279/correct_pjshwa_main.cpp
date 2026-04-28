#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int U[MAX + 1], V[MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    int x; cin >> x;
    U[x]++;
  }

  for (int i = 1; i <= M; i++) cin >> V[i];
  sort(V + 1, V + M + 1);

  for (int i = M; i >= 1; i--) {
    U[i] += U[i + 1], V[i] += V[i + 1];
    if (U[i] < V[i]) return cout << "NO\n", void();
  }
  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
