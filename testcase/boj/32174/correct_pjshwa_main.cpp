#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int P[MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= M; ++i) {
    int op; ll x; cin >> op >> x;
    if (op == 3) P[i] = P[x];

    x %= N;
    if (op == 1) P[i] = (P[i - 1] + x) % N;
    if (op == 2) P[i] = (P[i - 1] - x + N) % N;
  }
  cout << P[M] + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
