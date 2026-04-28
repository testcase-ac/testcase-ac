#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 98;
ll A[MAXN + 1];

ll f(ll N) {
  if (N <= MAXN) return A[N];

  ll nN = N / 3;
  switch (N % 3) {
    case 0: return 2 * (f(nN + 1) + nN) + 2;
    case 1: return 2 * (f(nN + 2) + nN) + 1;
    case 2: return 2 * (f(nN + 0) + nN) + 3;
  }
  assert(false);
  return 0;
}

void solve() {
  ll N; cin >> N;
  cout << f(N) << '\n';
}

int main() {
  fast_io();

  A[1] = 1, A[2] = 2;
  for (int i = 1; i <= 32; ++i) {
    A[3 * i + 0] = 2 * (A[i] + A[i + 1]) + 1;
    A[3 * i + 1] = 2 * A[i + 2] - 1;
    A[3 * i + 2] = -2 * (A[i + 1] + A[i + 2]) + 2;
  }
  for (int i = 2; i <= MAXN; ++i) A[i] += A[i - 1];

  int t = 1;
  cin >> t;
  while (t--) solve();
}
