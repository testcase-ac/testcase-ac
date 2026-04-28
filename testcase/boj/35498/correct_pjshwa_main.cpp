#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
ll D[MAXN], N, cnt = 0;

void update(int i, int v) {
  if (D[i] < 0) --cnt;
  D[i] += v;
  if (D[i] < 0) ++cnt;
}

void print_d() {
  cout << "D = {";
  for (int i = 0; i < N - 1; ++i) {
    cout << D[i];
    if (i < N - 2) cout << ", ";
  }
  cout << "}\n";
}

void solve() {
  int Q; cin >> N >> Q;
  for (int i = 0; i < N; ++i) {
    cin >> D[i];
    if (i > 0) D[i - 1] = D[i] - D[i - 1];
  }
  for (int i = 0; i < N - 1; ++i) if (D[i] < 0) ++cnt;

  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      int i, j, v; cin >> i >> j >> v; --i; --j;
      if (i > 0) update(i - 1, v);
      if (j < N - 1) update(j, -v);
    }
    if (op == 2) {
      if (cnt == 0) cout << "YES\n";
      else cout << "NO\n";
    }

    // print_d();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
