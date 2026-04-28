#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
int p[MAX + 1];

void solve() {
  int N, Q;
  cin >> N >> Q;
  for (int i = 1; i <= N; i++) cin >> p[i];
  sort(p + 1, p + N + 1);
  for (int i = 1; i <= N; i++) p[i] += p[i - 1];

  while (Q--) {
    int L, R;
    cin >> L >> R;
    cout << p[R] - p[L - 1] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
