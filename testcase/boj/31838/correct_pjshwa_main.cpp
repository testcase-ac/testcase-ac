#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int A[MAXN + 1], B[MAXN + 1];
ll dp[MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;

  ll sum = 0;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
    sum += A[i];
    B[i] = -A[i];
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
