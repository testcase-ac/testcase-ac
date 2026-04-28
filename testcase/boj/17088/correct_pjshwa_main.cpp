#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
int A[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  if (N <= 2) return cout << "0\n", void();

  int ans = INF;
  for (int d1 : {-1, 0, 1}) for (int d2 : {-1, 0, 1}) {
    int a1 = A[0] + d1, a2 = A[1] + d2, cur = abs(d1) + abs(d2);

    ll ac = a2, d = a2 - a1, able = 1;
    for (int i = 2; i < N; i++) {
      ac += d;
      if (abs(ac - A[i]) > 1) {
        able = 0;
        break;
      }
      cur += abs(ac - A[i]);
    }

    if (able) ans = min(ans, cur);
  }

  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
