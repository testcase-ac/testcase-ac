#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
pll A[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i].first >> A[i].second;
  sort(A, A + N);
  for (int i = 1; i < N; i++) A[i].second += A[i - 1].second;

  ll li = A[0].first, ans = 0;
  for (int i = 0; i < N; i++) {
    auto [ri, si] = A[i];
    ans = max(ans, si - ri + li);
    if (i < N - 1) li = max(li, A[i + 1].first - si);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
