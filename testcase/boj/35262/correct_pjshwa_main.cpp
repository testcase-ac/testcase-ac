#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; string S; cin >> N >> K >> S;

  vector<int> P(N + 1);
  for (int i = 1; i <= N; ++i) P[i] = P[i - 1] + (S[i - 1] == '0');
  for (int i = K; i <= N; ++i) {
    int cnt = P[i] - P[i - K];
    if (cnt == K) return cout << "0\n", void();
  }
  cout << "1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
