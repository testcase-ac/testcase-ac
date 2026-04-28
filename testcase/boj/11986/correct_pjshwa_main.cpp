#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
ll J[MAX + 10], JO[MAX + 10], OI[MAX + 10], I[MAX + 10];

void solve() {
  int N; string S; cin >> N >> S;

  for (int i = 1; i <= N; ++i) {
    char c = S[i - 1];

    if (c == 'J') J[i] = J[i - 1] + 1;
    else J[i] = J[i - 1];

    if (c == 'O') JO[i] = JO[i - 1] + J[i - 1];
    else JO[i] = JO[i - 1];
  }

  for (int i = N; i >= 1; --i) {
    char c = S[i - 1];

    if (c == 'I') I[i] = I[i + 1] + 1;
    else I[i] = I[i + 1];

    if (c == 'O') OI[i] = OI[i + 1] + I[i + 1];
    else OI[i] = OI[i + 1];
  }

  ll pre = 0;
  for (int i = 1; i <= N; ++i) {
    char c = S[i - 1];
    if (c == 'I') pre += JO[i - 1];
  }
  ll ans = pre;

  // find best place to put 'J'
  for (int i = 1; i <= N; ++i) {
    ans = max(ans, pre + OI[i]);
  }

  // find best place to put 'O'
  for (int i = 1; i <= N; ++i) {
    ans = max(ans, pre + J[i - 1] * I[i]);
  }

  // find best place to put 'I'
  for (int i = 1; i <= N; ++i) {
    ans = max(ans, pre + JO[i]);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
