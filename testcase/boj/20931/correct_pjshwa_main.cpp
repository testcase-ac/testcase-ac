#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int parent[MAX][20];
ll level[MAX];

void solve() {
  int Q;
  cin >> Q;

  ll last = 0, M = 1;
  while (Q--) {
    string op; ll x, L;
    cin >> op >> x >> L;
    if (op == "query") {
      for (int i = 19; i >= 0; i--) {
        ll diff = level[x] - level[parent[x][i]];
        if (diff <= L) {
          x = parent[x][i];
          L -= diff;
        }
      }
      last = x;
      cout << last << '\n';
    }
    if (op == "ad-hoc") {
      ll y = (x + last) % M;
      level[M] = level[y] + L;
      parent[M][0] = y;
      for (int j = 0; j < 20; j++) {
        if (parent[M][j]) parent[M][j + 1] = parent[parent[M][j]][j];
      }
      M++;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
