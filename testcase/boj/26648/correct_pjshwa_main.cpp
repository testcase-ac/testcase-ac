#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int A[MAX], B[MAX], C[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  for (int i = 0; i < N; i++) cin >> B[i];
  for (int i = 0; i < N; i++) cin >> C[i];

  int L = -1;
  for (int i = 0; i < N; i++) {
    int cmin = min({A[i], B[i], C[i]});
    int cmax = max({A[i], B[i], C[i]});
    if (cmax <= L) return cout << "NO\n", void();

    L = max(L + 1, cmin);
  }

  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
