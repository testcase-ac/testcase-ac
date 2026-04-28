#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 2e5, INF = 1e14;
ll P[MAX];

void solve() {
  int N;
  cin >> N;

  for (int i = 0; i < N; i++) cin >> P[i], P[i + N] = P[i];
  for (int i = 1; i < 2 * N; i++) P[i] += P[i - 1];

  ll left = 1, right = INF + 1;
  while (left < right) {
    ll mid = (left + right) / 2;

    bool f = false;
    for (int i = 0; i < N; i++) {
      ll acc = i == 0 ? 0 : P[i - 1];

      auto it1 = lower_bound(P, P + 2 * N, acc + mid);
      if (it1 == P + 2 * N) continue;
      ll pr1 = *it1 - acc;

      auto it2 = lower_bound(P, P + 2 * N, acc + 2 * pr1);
      if (it2 == P + 2 * N) continue;
      ll pr2 = *it2 - acc - pr1;

      ll pr3 = P[N - 1] - pr1 - pr2;

      if (pr1 <= pr2 && pr1 <= pr3) {
        f = true;
        break;
      }
    }

    if (f) left = mid + 1;
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
