#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
ll A[MAX];

void solve() {
  int N, K;
  cin >> N >> K;

  map<ll, ll> t;
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
    A[i] += A[i - 1];
    t[A[i]]++;
  }

  ll ans = t[K];
  for (int i = 1; i <= N; i++) {
    t[A[i]]--;
    ans += t[K + A[i]];
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
