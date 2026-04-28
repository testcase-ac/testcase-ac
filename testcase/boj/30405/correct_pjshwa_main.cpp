#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  vector<int> A;
  for (int i = 0; i < N; ++i) {
    int K; cin >> K;
    vector<int> B(K);
    for (int j = 0; j < K; ++j) cin >> B[j];
    A.push_back(B[0]); A.push_back(B.back());
  }

  sort(A.begin(), A.end());
  cout << A[N - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
