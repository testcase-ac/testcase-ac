#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
int A[MAXN], B[MAXN], Ac[MAXN + 1], Bc[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i], ++Ac[A[i]];
  int M; cin >> M;
  for (int i = 0; i < M; ++i) cin >> B[i], ++Bc[B[i]];

  int ai = 0, bi = 0;
  vector<int> V;
  for (int v = MAXN; v >= 1; --v) {
    int c = min(Ac[v], Bc[v]), acc_a = 0, acc_b = 0;
    while (acc_a < c) {
      if (A[ai] == v) ++acc_a;
      --Ac[A[ai]]; ++ai;
    }
    while (acc_b < c) {
      if (B[bi] == v) ++acc_b;
      --Bc[B[bi]]; ++bi;
    }
    while (c--) V.push_back(v);
  }

  cout << V.size() << '\n';
  for (int v : V) cout << v << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
