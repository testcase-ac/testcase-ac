#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1000;

void solve() {
  int N; cin >> N;

  int d[N + 1][16];
  memset(d, 0, sizeof(d)); d[0][15] = 1;

  for (int i = 1; i <= N; ++i) {
    for (int ps = 0; ps < 16; ++ps) for (int ns = 0; ns < 16; ++ns) {
      int p1 = ps & 1, p2 = ps & 2, p3 = ps & 4, p4 = ps & 8;
      int n1 = ns & 1, n2 = ns & 2, n3 = ns & 4, n4 = ns & 8;

      if (p1 == 0 && n1 == 0) continue;
      if (p2 == 0 && n2 == 0) continue;
      if (p3 == 0 && n3 == 0) continue;
      if (p4 == 0 && n4 == 0) continue;

      vector<int> v;
      if (p1 == 1 && n1 == 1) v.push_back(1);
      if (p2 == 2 && n2 == 2) v.push_back(2);
      if (p3 == 4 && n3 == 4) v.push_back(3);
      if (p4 == 8 && n4 == 8) v.push_back(4);

      if (v.size() % 2) continue;
      if (v.size() == 2 && abs(v[0] - v[1]) != 1) continue;

      d[i][ns] = (d[i][ns] + d[i - 1][ps]) % MOD;
    }
  }
  cout << d[N][15] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
