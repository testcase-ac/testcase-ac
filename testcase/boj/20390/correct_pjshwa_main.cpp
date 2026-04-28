#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
const ll INF = 1e18;
ll a, b, c, d;
ll x[MAX], mreach[MAX];
bool used[MAX];

ll dist(int i, int j) {
  if (i > j) swap(i, j);
  return (((__int128_t)x[i] * a + (__int128_t)x[j] * b) % c) ^ d;
}

int main() {
  fast_io();

  int n;
  cin >> n >> a >> b >> c >> d;
  for (int i = 0; i < n; i++) cin >> x[i];
  fill(mreach, mreach + n, INF);

  // Modified Prim's algorithm
  ll ans = 0;
  mreach[0] = 0;

  for (int i = 0; i < n; i++) {
    ll wgt = INF;
    int sv = -1;
    for (int j = 0; j < n; j++) {
      if (used[j]) continue;
      if (mreach[j] < wgt) sv = j, wgt = mreach[j];
    }

    used[sv] = true;
    ans += wgt;

    for (int to = 0; to < n; to++) mreach[to] = min(mreach[to], dist(sv, to));
  }

  cout << ans << '\n';
}
