#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M;
  cin >> N >> M;

  string S;
  cin >> S;
  for (int i = 1; i < N; i++) {
    string T;
    cin >> T;
    
    // check for overlapping string
    bool ok = false;
    for (int j = 0; j < 2 * M - 1; j++) {
      int ss = max(0, j - M + 1), se = min(M - 1, j);
      int ts = max(0, M - 1 - j), te = min(M - 1, M - 1 + M - 1 - j);
      if (S.substr(ss, se - ss + 1) == T.substr(ts, te - ts + 1)) {
        ok = true;
        break;
      }
    }

    if (!ok) return cout << "0\n", void();
    S = T;
  }

  cout << "1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
