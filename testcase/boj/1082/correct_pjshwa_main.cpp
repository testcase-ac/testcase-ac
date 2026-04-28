#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

struct G {
  int d[10] = {0}, sz = 0;

  bool operator<(const G& rhs) const {
    bool lhs_az = sz == d[0], rhs_az = rhs.sz == rhs.d[0];
    if (lhs_az && rhs_az) return sz < rhs.sz;
    if (lhs_az && !rhs_az) return true;
    if (!lhs_az && rhs_az) return false;

    if (sz != rhs.sz) return sz < rhs.sz;
    for (int i = 9; i >= 0; i--) {
      if (d[i] != rhs.d[i]) return d[i] < rhs.d[i];
    }
    return false;
  }

  void print() {
    bool az = sz == d[0];
    if (az) return cout << "0\n", void();
    for (int i = 9; i >= 0; i--) {
      for (int j = 0; j < d[i]; j++) {
        cout << i;
      }
    }
    cout << '\n';
  }
};

G d[51];
void solve() {
  int N;
  cin >> N;

  int P[N], M;
  for (int i = 0; i < N; i++) cin >> P[i];
  cin >> M;

  for (int i = N - 1; i >= 0; i--) {
    for (int v = P[i]; v <= M; v++) {
      G g = d[v - P[i]];
      g.d[i]++;
      g.sz++;
      d[v] = max(d[v], g);
    }
  }

  d[M].print();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
