#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 11;
int S[MAXN], E[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> S[i] >> E[i];
  for (int i = 0; i < N; ++i) {
    int s, e; cin >> s >> e;
    S[i] = max(S[i], s); E[i] = min(E[i], e);
  }

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    if (S[i] > E[i]) return cout << "-1\n", void();
    ans += S[i] < E[i];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
