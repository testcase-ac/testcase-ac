#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 12;
int b[MAX][MAX], d[1 << MAX][1 << MAX];
int n, m;

void fold(vector<int>& v, set<vector<int>>& s) {
  s.insert(v);
  int n = v.size();
  for (int i = 1; i < n; i++) {
    int j = 0;
    vector<int> nv;
    if (2 * i <= n) {
      while (i - j > 0) {
        nv.push_back(v[i + j] | v[i - j - 1]);
        j++;
      }
      for (int k = i + j; k < n; k++) nv.push_back(v[k]);
    }
    else {
      while (i + j < n) {
        nv.push_back(v[i + j] | v[i - j - 1]);
        j++;
      }
      for (int k = i - j - 1; k >= 0; k--) nv.push_back(v[k]);
    }
    fold(nv, s);
  }
}

int c(int iv, int jv) {
  if (d[iv][jv] != -1) return d[iv][jv];

  int dv = 0;
  for (int i = 0; i < n; i++) {
    if (!(iv & (1 << i))) continue;
    for (int j = 0; j < m; j++) {
      if (jv & (1 << j)) dv += b[i][j];
    }
  }
  return d[iv][jv] = dv;
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> b[i][j];
  memset(d, -1, sizeof(d));

  set<vector<int>> s1, s2;
  vector<int> f1, f2;
  for (int i = 0; i < n; i++) f1.push_back(1 << i);
  for (int i = 0; i < m; i++) f2.push_back(1 << i);
  fold(f1, s1);
  fold(f2, s2);

  set<int> sv1, sv2;
  for (auto comb1 : s1) for (int iv : comb1) sv1.insert(iv);
  for (auto comb2 : s2) for (int jv : comb2) sv2.insert(jv);

  int mx = -1e9;
  for (auto iv : sv1) for (auto jv : sv2) {
    mx = max(mx, c(iv, jv));
  }

  cout << mx << '\n';
}
