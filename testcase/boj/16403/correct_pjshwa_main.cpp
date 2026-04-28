#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
ll U[MAX + 1], d[MAX + 1];

void solve() {
  ll N, A, B;
  cin >> N >> A >> B;
  for (int i = 1; i <= N; i++) cin >> U[i];
  sort(U + 1, U + N + 1);

  for (int i = 1; i <= N; i++) {
    d[i] = d[i - 1] + U[i] * A;

    for (int j = i; j > i - 40; j--) {
      if (j <= 0) break;

      // Optimal to take bus in the middle.
      ll cost = 0, m = (i + j) / 2;
      for (int k = j; k <= i; k++) cost += abs(U[k] - U[m]);

      d[i] = min(d[i], d[j - 1] + cost * A + B);
    }
  }

  cout << d[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
