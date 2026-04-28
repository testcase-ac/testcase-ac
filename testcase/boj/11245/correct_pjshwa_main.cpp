#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

matrix operator * (const matrix &a, const matrix &b) {
  int n = a.size();
  matrix c(n, vector<ll>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
    }
  }
  return c;
}

void solve() {
  matrix S = matrix(26, vector<ll>(26));
  for (int i = 0; i < 26; i++) for (int j = 0; j < 26; j++) cin >> S[i][j];

  int q;
  cin >> q;
  while (q--) {
    string C; int L;
    cin >> C >> L;
    if (L == 1) {
      cout << "0\n";
      continue;
    }

    L -= 2;
    matrix ans = matrix(26, vector<ll>(26));
    matrix a = matrix(26, vector<ll>(26));
    for (int i = 0; i < 26; i++) for (int j = 0; j < 26; j++) ans[i][j] = a[i][j] = S[i][j];

    while (L) {
      if (L & 1) ans = ans * a;
      a = a * a;
      L /= 2;
    }

    ll res = 0;
    for (int i = 0; i < 26; i++) res = max(res, ans[C[0] - 'A'][i]);
    cout << res << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
