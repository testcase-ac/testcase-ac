#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S, A, B; cin >> S >> A >> B;
  int N = S.size(), M = A.size(), i = 0;
  for (int j = 0; j < M; ++j) {
    if (i < N && (A[j] == '*' || A[j] == S[i] || B[j] == S[i])) ++i;
  }
  cout << (i == N ? "win" : "lose") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
