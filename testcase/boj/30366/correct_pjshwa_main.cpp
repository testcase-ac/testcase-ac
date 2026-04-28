#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  reverse(A.begin(), A.end());

  int t = 0;
  while (!A.empty()) {
    int acc = 0;
    while (!A.empty() && acc + A.back() <= M) {
      acc += A.back();
      A.pop_back();
      cout << t << '\n';
    }
    ++t;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
