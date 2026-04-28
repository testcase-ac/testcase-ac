#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int M, N, Q; cin >> M >> N >> Q;
  for (int i = 0; i < N; i++) cin >> Q;

  vector<int> ans(N, 1);
  for (int i = 1; i <= M; i++) {
    cout << "? " << i << ' ' << i << endl;

    int x; cin >> x;
    if (x == 1) ans[i - 1] = 2;
  }

  cout << "! ";
  for (int i = 0; i < N; i++) cout << ans[i] << ' ';
  cout << endl;
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
