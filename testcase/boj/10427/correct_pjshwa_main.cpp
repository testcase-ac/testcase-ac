#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A.begin(), A.end());

  vector<ll> S(N, 1e18); S[0] = 0;
  for (int i = 1; i < N; i++) {
    ll run = 0;
    for (int j = i - 1; j >= 0; j--) {
      run += A[i] - A[j];
      S[i - j] = min(S[i - j], run);
    }
  }
  cout << reduce(S.begin(), S.end()) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
