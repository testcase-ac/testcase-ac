#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
ll A[MAXN + 1];

void solve() {
  int N, C, Y; cin >> N >> C >> Y;

  ll sum = 0;
  for (int i = 1; i <= N; ++i) cin >> A[i], sum += A[i];

  set<int> R; ll cnt = 0;
  for (int i = 1; i <= N; ++i) {
    if (i == C) continue;
    R.insert(A[i] % (Y + 1));
    cnt = max(cnt, A[i]);
  }
  if (R.size() > 1) return cout << "impossible\n", void();

  cout << cnt << ' ' << sum + (ll)(Y - (N - 1)) * cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
