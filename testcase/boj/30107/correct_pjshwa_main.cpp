#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
int P1[MAX + 1], P2[MAX + 1];

int f(int n) {
  int L = 3;
  while (n >= L) L = 2 * L + 1;
  return (L - 1) / 2;
}

void solve() {
  ll N, A, B; cin >> N >> A >> B;
  if (A < B) swap(A, B);
  cout << P1[N] * A + P2[N] * B << '\n';
}

int main() {
  fast_io();

  for (int i = 1; i <= MAX; ++i) {
    int val = f(i);
    P1[i] = P1[i - 1] + __builtin_popcount(val);
    P2[i] = P2[i - 1] + __builtin_popcount(i - val);
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
