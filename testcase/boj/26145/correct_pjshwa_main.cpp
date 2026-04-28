#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M;
  cin >> N >> M;
  
  vector<int> S(N);
  for (int i = 0; i < N; i++) cin >> S[i];

  vector<int> A(N + M);
  for (int i = 0; i < N; i++) A[i] += S[i];

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N + M; j++) {
      int x;
      cin >> x;
      A[i] -= x;
      A[j] += x;
    }
  }

  for (int i = 0; i < N + M; i++) {
    cout << A[i] << " \n"[i == N + M - 1];
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
