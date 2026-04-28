#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int A[8] = {
  0, 1906, 0, 2026, 0, 12106, 0, 1003906,
};

void solve() {
  int N; cin >> N;
  if (N < 8) cout << A[N] << '\n';
  else {
    string ans(N, '0');
    ans[0] = '1'; ans[N / 2] = '2';

    string T = "6091";
    for (int i = 0; i < 4; ++i) ans[N - 1 - i] = T[i];
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
