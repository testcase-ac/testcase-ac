#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3e5, LIM = 1e9;
ll A[MAX + 5], C[MAX + 5];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  int left = 2, right = N + 1;
  while (left < right) {
    int mid = (left + right) / 2;

    memset(C, 0, sizeof(C));
    for (int i = 0; i < N; i++) {
      if (A[i] < mid) C[A[i]]++;
      else C[0]++;
    }

    ll ded = 1;
    for (int i = mid - 1; i >= 2; i--) {
      ll e = C[i] - ded;
      if (e >= 0) C[0] += e;
      else ded += -e;

      if (ded > LIM) break;
    }

    if (C[0] + C[1] >= 2 * ded) left = mid + 1;
    else right = mid;
  }

  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
