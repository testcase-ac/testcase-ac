#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1e5, INF = 1e18;
int A[MAX], N;

ll f(ll d) {
  ll ret = 0;
  for (int i = 0; i < N; i++) ret += abs(A[i] - d * i);
  return ret;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N);

  // Ternary search
  ll left = 1, right = 1e9 + 1;
  while (left + 3 <= right) {
    ll mid1 = left + (right - left) / 3;
    ll mid2 = right - (right - left) / 3;

    if (f(mid1) < f(mid2)) right = mid2;
    else left = mid1;
  }

  ll ans = INF;
  for (ll i = left; i <= right; i++) ans = min(ans, f(i));
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
