#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, INF = 1e9 + 7;
int h[MAX];

matrix operator * (const matrix &a, const matrix &b) {
  int n = a.size();
  matrix c(n, vector<ll>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]);
    }
  }
  return c;
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> h[i];

  matrix o = matrix(n, vector<ll>(n));
  for (int i = 0; i < n; i++) o[i][i] = 1;

  matrix a = matrix(n, vector<ll>(n));
  while (m--) {
    int x, y;
    cin >> x >> y;
    a[x - 1][y - 1]++;
    a[y - 1][x - 1]++;
  }

  int q;
  cin >> q;
  vector<int> ans(q);
  vector<tuple<int, int, int>> qs;
  for (int i = 0; i < q; i++) {
    int ai, ki;
    cin >> ai >> ki;
    qs.push_back({ki, ai - 1, i});
  }
  sort(qs.begin(), qs.end());

  int qi = 0;
  for (int k = 1; k <= 500; k++) {
    o = o * a;
    while (qi < q && get<0>(qs[qi]) == k) {
      auto [ki, ai, oi] = qs[qi];

      int x = INF;
      for (int i = 0; i < n; i++) {
        if (o[i][ai] == 0) continue;
        x = min(x, h[i]);
      }

      if (x == INF) ans[oi] = -1;
      else ans[oi] = x;

      qi++;
    }
  }

  for (int e : ans) cout << e << '\n';

}
