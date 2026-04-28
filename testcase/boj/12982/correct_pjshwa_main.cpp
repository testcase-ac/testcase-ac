#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
ll A[MAX];

void solve() {
  int N;
  cin >> N;

  ll pre = 0, ans = 1e18;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    pre += (A[i] / N);
    A[i] %= N;
  }

  sort(A, A + N);
  for (int i = 0; i < N; i++) {
    ll cur = A[i] + (N - i - 1);
    ans = min(ans, cur);
  }
  cout << ans + pre << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
