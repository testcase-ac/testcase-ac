#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int A[MAX + 1], B[MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i], A[i] += A[i - 1];
  for (int i = 1; i <= N; i++) cin >> B[i], B[i] += B[i - 1];

  map<int, int> t;
  for (int i = 1; i <= N; i++) t[B[i] - A[i]]++;

  ll ans = 0, cdiff = 0;
  for (int i = 1; i <= N; i++) {
    ans += t[cdiff];
    cdiff = B[i] - A[i];
    t[cdiff]--;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
