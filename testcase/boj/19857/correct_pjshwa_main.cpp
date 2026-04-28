#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 5e5, LIM = 1e15;
ll O[MAX + 5], C[MAX + 5];

void solve() {
  int N; cin >> N; ll L = 0;
  for (int i = 0; i < N; i++) cin >> O[i], L += O[i];

  if (L == 1) {
    for (int i = 0; i < N; i++) {
      if (O[i] == 1) return cout << max(1, i) << '\n', void();
    }
  }

  ll left = 2, right = MAX + 1;
  while (left < right) {
    int mid = (left + right) / 2;

    memset(C, 0, sizeof(C));
    for (int i = 0; i < N; i++) {
      if (i < mid) C[i] = O[i];
      else C[0] += O[i];
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
