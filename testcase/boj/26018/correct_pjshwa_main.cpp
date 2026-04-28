#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e4;
int C[MAXN + 1];

void solve() {
  int N = 0;
  for (int t = 0; t < 5; ++t) {
    cout << "? ";
    for (int c = 1; c <= 26; ++c) {
      if (c & (1 << t)) cout << (char)('a' + c - 1);
    }
    cout << endl;

    int x, c; cin >> x;
    while (x--) {
      cin >> c; N = max(N, c);
      C[c] |= (1 << t);
    }
  }

  cout << "! ";
  for (int i = 1; i <= N; ++i) cout << (char)('a' + C[i] - 1);
  cout << endl;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
