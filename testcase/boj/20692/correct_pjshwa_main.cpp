#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MOD = 998244353;
vector<int> P, Q;
int N;

void transform() {
  for (int i = 1; i <= N; i++) Q[i] = P[P[i]];
  for (int i = 1; i <= N; i++) P[i] = Q[i];
}

void solve() {
  cin >> N;
  P.resize(N + 1); Q.resize(N + 1);
  for (int i = 1; i <= N; i++) cin >> P[i];

  set<vector<int>> S; S.insert(P);
  for (int k = 0;; k++) {
    transform();
    if (S.count(P)) break;
    S.insert(P);
  }
  cout << S.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
