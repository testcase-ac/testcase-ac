#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
ll A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  ll dt = 0, all = 0, tar = A[0], mdiff = 0;
  for (int i = 1; i < N; ++i) {
    ll cur = A[i] + dt;
    ll diff = abs(tar - cur);
    all += diff;
    mdiff = max(mdiff, diff);
    dt += tar - cur;
  }

  ll ans = all - mdiff;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
