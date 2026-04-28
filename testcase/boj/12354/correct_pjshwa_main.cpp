#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";
  
  int N; cin >> N;
  vector<int> A(N), d(N, 1);

  int ans = 0;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    for (int j = 0; j < i; j++) {
      if (A[j] < A[i]) d[i] = max(d[i], d[j] + 1);
    }
    ans = max(ans, d[i]);
  }
  cout << N - ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
