#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int Q; cin >> Q;
  while (Q--) {
    int S, E; cin >> S >> E;
    int da = S, db = S, na = 0, nb = 0;
    while (da != E) da = da == 243 ? 201 : da + 1, ++na;
    while (db != E) db = db == 201 ? 243 : db - 1, ++nb;
    if (na < nb) cout << "Inner circle line\n";
    else if (na == nb) cout << "Same\n";
    else cout << "Outer circle line\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
