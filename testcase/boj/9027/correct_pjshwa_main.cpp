#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1e5, INF = 1e18;
ll A[MAX], B[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  for (int i = 0; i < N; i++) cin >> B[i];

  ll ldist = 0, rdist = 0, lwgt = 0, rwgt = 0, ans, apos;
  for (int i = 1; i < N; i++) {
    ll dis = A[i] - A[0], wgt = B[i];
    rdist += dis * wgt;
    rwgt += wgt;
  }
  ans = rdist, apos = A[0];

  for (int i = 1; i < N; i++) {
    lwgt += B[i - 1];
    ldist += (A[i] - A[i - 1]) * lwgt;

    rdist -= (A[i] - A[i - 1]) * rwgt;
    rwgt -= B[i];

    if (ans > ldist + rdist) {
      ans = ldist + rdist;
      apos = A[i];
    }
  }
  cout << apos << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
