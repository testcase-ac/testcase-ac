#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int A[MAXN], Lmax[MAXN], Lmin[MAXN], Rmax[MAXN], Rmin[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  stack<pii> T;
  for (int i = 0; i < N; ++i) {
    while (!T.empty() && T.top().first < A[i]) T.pop();
    Lmax[i] = T.empty() ? -1 : T.top().second;
    T.push({A[i], i});
  }
  T = stack<pii>();
  for (int i = 0; i < N; ++i) {
    while (!T.empty() && T.top().first > A[i]) T.pop();
    Lmin[i] = T.empty() ? -1 : T.top().second;
    T.push({A[i], i});
  }
  T = stack<pii>();
  for (int i = N - 1; i >= 0; --i) {
    while (!T.empty() && T.top().first <= A[i]) T.pop();
    Rmax[i] = T.empty() ? N : T.top().second;
    T.push({A[i], i});
  }
  T = stack<pii>();
  for (int i = N - 1; i >= 0; --i) {
    while (!T.empty() && T.top().first >= A[i]) T.pop();
    Rmin[i] = T.empty() ? N : T.top().second;
    T.push({A[i], i});
  }

  ll ans = 0;
  for(int i = 0; i < N; ++i) {
    ll cnt = (ll)(Rmax[i] - i) * (i - Lmax[i]);
    cnt -= (ll)(Rmin[i] - i) * (i - Lmin[i]);
    ans += A[i] * cnt;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
