#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;

  int N = S.size();
  vector<int> pi(N), A(N);
  for (int i = 1, j = 0; i < N; i++) {
    while (j && S[i] != S[j]) j = pi[j - 1];
    if (S[i] == S[j]) pi[i] = ++j;
    if (i < N - 1) A[pi[i]] = 1;
  }

  int x = pi[N - 1];
  while (x && !A[x]) x = pi[x - 1];
  if (x) cout << S.substr(0, x) << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
