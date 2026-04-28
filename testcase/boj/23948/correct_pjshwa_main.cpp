#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
ll A[MAX], c[MAX], f[MAX];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  ll N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> A[i];

  memset(c, 0, sizeof(c));
  memset(f, 0, sizeof(f));

  ll sum = 0;
  for (int b = 0; b < 50; b++) {
    for (int i = 0; i < N; i++) {
      if (A[i] & (1LL << b)) c[b]++;
    }

    ll a1 = (1LL << b) * c[b];
    ll a2 = (1LL << b) * (N - c[b]);
    if (a1 >= a2) f[b] = 1;
    sum += min(a1, a2);
  }
  if (sum > M) return cout << "-1\n", void();

  for (int b = 49; b >= 0; b--) {
    if (f[b]) continue;

    ll a1 = (1LL << b) * c[b];
    ll a2 = (1LL << b) * (N - c[b]);
    ll addend = a2 - a1;
    if (sum + addend > M) continue;

    sum += addend;
    f[b] = 1;
  }

  ll ans = 0;
  for (int b = 0; b < 50; b++) {
    if (f[b]) ans |= (1LL << b);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
