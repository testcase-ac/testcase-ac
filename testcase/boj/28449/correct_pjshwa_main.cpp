#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, M; cin >> N >> M;

  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A.begin(), A.end());

  ll answ = 0, ansd = 0;
  for (int i = 0; i < M; i++) {
    int x; cin >> x;
    auto lb = lower_bound(A.begin(), A.end(), x);
    auto ub = upper_bound(A.begin(), A.end(), x);
    answ += lb - A.begin();
    ansd += ub - lb;
  }
  cout << N * M - answ - ansd << ' ' << answ << ' ' << ansd << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
