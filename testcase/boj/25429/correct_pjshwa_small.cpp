#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int cval[MAX + 1];

void solve() {
  int N, l, Q;
  cin >> N >> l >> Q;

  while (Q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int x, t;
      cin >> x >> t;
      cval[x] = t;
    }
    if (op == 2) {
      int x;
      cin >> x;
      cval[x] = 0;
    }

    bool able = true;
    ll rsum = 0;
    for (int i = 0; i < l; i++) {
      set<int> u;
      for (int j = 0; j < N / l; j++) {
        int idx = j * l + i;
        if (idx == 0) idx = N;
        if (cval[idx]) u.insert(cval[idx]);
      }
      if (u.size() > 1) able = false;
      else if (u.size() == 1) rsum += *u.begin();
    }

    if (able) cout << "YES " << rsum << '\n';
    else cout << "NO\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
