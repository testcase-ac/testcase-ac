#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B, N;
  cin >> A >> B >> N;
  vector<int> p(N);
  for (int i = 0; i < N; i++) cin >> p[i];

  int ans = abs(A - B);
  for (int i = 0; i < N; i++) {
    ans = min(ans, abs(p[i] - B) + 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
