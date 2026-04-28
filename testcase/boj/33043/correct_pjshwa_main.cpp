#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
string S[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> S[i];

  int l = 1, r = N + 1;
  map<string, int> tal;
  while (l < r) {
    tal.clear();
    int m = (l + r) / 2, ok = 0;
    for (int i = 1; i <= N; ++i) {
      if (i > m) --tal[S[i - m]];
      if (++tal[S[i]] == 5) ok = 1;
    }
    if (ok) r = m;
    else l = m + 1;
  }

  int ans = l == N + 1 ? -1 : l;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
