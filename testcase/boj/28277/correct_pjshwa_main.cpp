#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
set<int> SS[MAX + 1];

void solve() {
  int N, Q; cin >> N >> Q;
  for (int i = 1; i <= N; i++) {
    int Si; cin >> Si;
    for (int j = 0; j < Si; j++) {
      int x; cin >> x;
      SS[i].insert(x);
    }
  }

  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      int a, b; cin >> a >> b;
      if (SS[a].size() > SS[b].size()) {
        for (int x : SS[b]) SS[a].insert(x);
        SS[b].clear();
      }
      else {
        for (int x : SS[a]) SS[b].insert(x);
        SS[a].clear();
        swap(SS[a], SS[b]);
      }
    }
    else {
      int x; cin >> x;
      cout << SS[x].size() << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
