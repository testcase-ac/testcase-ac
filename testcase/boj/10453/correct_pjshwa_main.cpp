#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int posb[MAX + 1];

void solve() {
  string A, B;
  cin >> A >> B;
  if (A.size() != B.size()) return cout << "-1\n", void();

  int p = 0, n = A.size();
  for (int i = 0; i < n; i++) {
    if (A[i] == 'b') posb[p++] = i;
  }

  ll bp = 0, bcount = 0, ans = 0;
  for (int i = 0; i < n; i++) {
    if (B[i] == 'b') {
      bcount++;
      ans += abs(posb[bp++] - i);
    }
  }

  if (p == bcount) cout << ans << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
