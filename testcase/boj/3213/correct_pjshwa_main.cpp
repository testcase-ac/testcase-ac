#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int q1 = 0, q2 = 0, q3 = 0;
  for (int i = 0; i < N; i++) {
    string S; cin >> S;
    if (S == "1/4") q1++;
    if (S == "1/2") q2++;
    if (S == "3/4") q3++;
  }

  int ans = 0;
  int qz = min(q1, q3); q1 -= qz; q3 -= qz; ans += qz;
  int qm = q2 / 2; q2 -= 2 * qm; ans += qm;
  if (q2) {
    q2 = 0; q1 -= min(q1, 2); ans++;
  }
  if (q1) ans += (q1 - 1) / 4 + 1;
  if (q3) ans += q3;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
