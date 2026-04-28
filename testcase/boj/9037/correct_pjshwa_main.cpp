#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 10;
int A[MAXN], B[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  for (int it = 0;; ++it) {
    set<int> U;
    for (int i = 0; i < N; ++i) {
      if (A[i] & 1) A[i] += 1;
      U.insert(A[i]);
    }
    if (U.size() == 1) return cout << it << '\n', void();

    for (int i = 0; i < N; ++i) B[(i + 1) % N] = A[i] / 2;
    for (int i = 0; i < N; ++i) A[i] = A[i] / 2 + B[i];
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
