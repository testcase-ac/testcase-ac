#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int pi[MAXN];

void solve() {
  string S; cin >> S;
  int N = S.size();
  for (int i = 1, j = 0; i < N; ++i) {
    while (j && S[i] != S[j]) j = pi[j - 1];
    if (S[i] == S[j]) pi[i] = ++j;
  }

  for (int i = 0; i < N; ++i) {
    int l = i + 1, p = l - pi[i];
    if (pi[i] > 0 && l % p == 0) cout << l << ' ' << l / p << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
