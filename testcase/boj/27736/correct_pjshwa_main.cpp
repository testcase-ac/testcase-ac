#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int P = 0, D = 0, A = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    if (x == +1) P++;
    if (x == -1) D++;
    if (x == 0) A++;
  }

  if (2 * A >= N) cout << "INVALID\n";
  else if (P > D) cout << "APPROVED\n";
  else cout << "REJECTED\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
