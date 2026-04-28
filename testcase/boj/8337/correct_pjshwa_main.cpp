#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

// sum of d(1)..d(N)
ll sum_d(ll N) {
  ll ret = 0, q = sqrt(N);
  for (int i = 1; i <= q; i++) ret += N / i;
  ret = 2 * ret - q * q;
  return ret;
}

void solve() {
  int N;
  cin >> N;

  ll sds = sum_d(N), sqs = 0;
  for (int i = 1; i * i <= N; i++) sqs++;
  cout << (sds + sqs) / 2 << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}