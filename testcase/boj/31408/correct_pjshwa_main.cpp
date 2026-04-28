#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int T[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    ++T[x];
  }

  for (int i = 1; i <= MAXN; ++i) {
    if (T[i] > (N + 1) / 2) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
