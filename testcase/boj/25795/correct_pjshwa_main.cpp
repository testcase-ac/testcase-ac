#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e5;
ll S, N, b, c, mmax;

void dfs(int wc, int bc) {
  if (wc == N && bc == N) {
    mmax = max(mmax, S);
    return;
  }

  ll pS;
  if (wc < N) {
    pS = S;
    S = (S + b) % MOD;
    dfs(wc + 1, bc);
    S = pS;
  }
  if (bc < wc) {
    pS = S;
    S = (S * c) % MOD;
    dfs(wc, bc + 1);
    S = pS;
  }
}

void solve() {
  cin >> N >> S >> b >> c;

  dfs(0, 0);
  cout << mmax << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
