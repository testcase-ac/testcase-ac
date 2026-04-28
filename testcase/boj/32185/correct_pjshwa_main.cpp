#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  int A[3]; cin >> A[0] >> A[1] >> A[2];
  int S = A[0] + A[1] + A[2];

  vector<pair<int, int>> B;
  for (int i = 0; i < N; ++i) {
    cin >> A[0] >> A[1] >> A[2];
    int T = A[0] + A[1] + A[2];
    if (T > S) continue;
    B.emplace_back(T, i + 1);
  }
  sort(B.begin(), B.end());

  cout << "0 "; --M;
  for (int i = 0; i < M; ++i) {
    if (B.empty()) break;
    cout << B.back().second << ' ';
    B.pop_back();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
