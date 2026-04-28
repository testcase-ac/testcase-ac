#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, L; cin >> N >> M >> L;
  int W = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    W += x;
  }

  if (W == M) cout << "0\n";
  else if (W > M) cout << "-1\n";
  else if (W >= L) cout << "1\n";
  else if ((M - W) >= L) cout << "1\n";
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
