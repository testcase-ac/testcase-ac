#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
ll Px[MAXN + 1], Py[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> Px[i] >> Py[i];
  sort(Px + 1, Px + N + 1);
  sort(Py + 1, Py + N + 1);
  for (int i = 1; i <= N; ++i) {
    Px[i] += Px[i - 1];
    Py[i] += Py[i - 1];
  }

  ll ans = 0;
  for (int i = 1; i <= N; ++i) {
    int lcnt = i - 1, rcnt = N - i;
    ll x = Px[i] - Px[i - 1], y = Py[i] - Py[i - 1];
    ll lsumx = Px[i - 1], rsumx = Px[N] - Px[i];
    ll lsumy = Py[i - 1], rsumy = Py[N] - Py[i];
    ans += x * lcnt - lsumx + rsumx - x * rcnt;
    ans += y * lcnt - lsumy + rsumy - y * rcnt;
  }
  cout << ans / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
