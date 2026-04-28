#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int A[MAXN], pi[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  reverse(A, A + N);
  for (int i = 1, j = 0; i < N; ++i) {
    while (j && A[i] != A[j]) j = pi[j - 1];
    if (A[i] == A[j]) pi[i] = ++j;
  }

  int ck = 0, cp = N;
  for (int i = 0; i < N; ++i) {
    int k = N - i - 1, p = i + 1 - pi[i];
    if (k + p < ck + cp) ck = k, cp = p;
    else if (k + p == ck + cp && p < cp) ck = k, cp = p;
  }
  cout << ck << ' ' << cp << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
