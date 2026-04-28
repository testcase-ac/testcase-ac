#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  stack<int> s[4];
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;

    int pj = -1, pv = -1;
    for (int j = 0; j < 4; j++) {
      int sv;
      if (s[j].empty()) sv = 0;
      else sv = s[j].top();

      if (sv < x && pv < sv) {
        pj = j;
        pv = sv;
      }
    }
    if (pj == -1) return cout << "NO\n", void();
    s[pj].push(x);
  }

  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
