#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
ll A[MAX + 1], d[MAX + 1];

void solve() {
  int N, K, Q; cin >> N >> K >> Q;
  for (int i = 1; i <= N; i++) cin >> A[i];

  int streak = 0;
  for (int i = 1; i <= N; i++) {
    if (A[i] == K) streak = 0;
    else streak++;
    d[i] = d[i - 1] + streak;
  }

  while (Q--) {
    int r; cin >> r;
    cout << d[r] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
