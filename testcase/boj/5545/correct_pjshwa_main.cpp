#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, A, B, C; cin >> N >> A >> B >> C;

  vector<int> D(N);
  for (int i = 0; i < N; i++) cin >> D[i];
  sort(D.begin(), D.end(), greater<int>());

  double ans = (double)C / A;
  int cal = C, cost = A;
  for (int i = 0; i < N; i++) {
    cal += D[i]; cost += B;
    ans = max(ans, (double)cal / cost);
  }
  cout << (int)ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
