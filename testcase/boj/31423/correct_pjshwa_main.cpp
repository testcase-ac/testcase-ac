#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
string S[MAXN + 1];
int E[MAXN + 1], P[MAXN + 1], V[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> S[i];

  iota(E + 1, E + N + 1, 1);
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    P[E[u]] = v;
    E[u] = E[v];
    V[v] = 1;
  }

  int s;
  for (s = 1; s <= N; ++s) if (!V[s]) break;
  while (s) {
    cout << S[s];
    s = P[s];
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
