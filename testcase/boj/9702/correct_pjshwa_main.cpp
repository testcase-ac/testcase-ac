#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, ans = 0; cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  for (int i = 0; i < N; i++) {
    vector<int> L{-A[i]}; ans++;
    for (int j = i - 1; j >= 0; j--) {
      int x = -A[j];
      if (x > L.back()) L.push_back(x);
      else {
        auto it = lower_bound(L.begin(), L.end(), x);
        *it = x;
      }
      ans += L.size();
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
