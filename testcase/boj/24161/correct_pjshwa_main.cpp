#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll C[26], W[21], N;
ll fac[21];

void rec(int i, ll L) {
  if (i == N) {
    cout << L << '\n';
    return;
  }

  ll acc = 0;
  for (int ci = 0; ci < 26; ++ci) {
    if (C[ci] == 0) continue;

    --C[ci];
    if (W[i] == ci) return rec(i + 1, L + acc);

    ll cur = fac[N - i - 1];
    for (int j = 0; j < 26; ++j) cur /= fac[C[j]];
    acc += cur;
    ++C[ci];
  }
}

void solve() {
  string S; cin >> S;
  N = S.size();
  for (int i = 0; i < N; ++i) {
    int ci = S[i] - 'A';
    ++C[ci]; W[i] = ci;
  }
  rec(0, 1);
}

int main() {
  fast_io();

  fac[0] = 1;
  for (int i = 1; i <= 20; ++i) fac[i] = fac[i - 1] * i;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
