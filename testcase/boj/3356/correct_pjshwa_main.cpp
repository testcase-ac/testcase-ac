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
  int N; string S; cin >> N >> S;
  for (int i = 1, j = 0; i < N; ++i) {
    while (j && S[i] != S[j]) j = pi[j - 1];
    if (S[i] == S[j]) pi[i] = ++j;
  }
  cout << N - pi[N - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
