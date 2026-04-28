#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

// Credit: https://github.com/ShahjalalShohag/code-library/blob/master/Math/Gaussian%20Elimination%20Modular.cpp
ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

int Gauss(vector<vector<int>>& a, vector<int> &ans, ll mod) {
  int n = a.size(), m = (int)a[0].size() - 1;
  vector <int> pos(m, -1);

  int free_var = 0;
  const long long MODSQ = (long long)mod * mod;
  int det = 1, rank = 0;

  for (int col = 0, row = 0; col < m && row < n; col++) {
    int mx = row;
    for (int k = row; k < n; k++) if (a[k][col] > a[mx][col]) mx = k;
    if (a[mx][col] == 0) {det = 0; continue;}
    for (int j = col; j <= m; j++) swap(a[mx][j], a[row][j]);
    if (row != mx) det = det == 0 ? 0 : mod - det;
    det = 1LL * det * a[row][col] % mod;
    pos[col] = row;

    int inv = lpow(a[row][col], mod - 2, mod);
    for (int i = 0; i < n && inv; i++){
      if (i != row && a[i][col]) {
        int x = ((long long)a[i][col] * inv) % mod;
        for (int j = col; j <= m && x; j++){
          if (a[row][j]) a[i][j] = (MODSQ + a[i][j] - ((long long)a[row][j] * x)) % mod;
        }
      }
    }
    row++; ++rank;
  }

  ans.assign(m, 0);
  for (int i = 0; i < m; i++){
    if (pos[i] == -1) free_var++;
    else ans[i] = ((long long)a[pos[i]][m] * lpow(a[pos[i]][i], mod - 2, mod)) % mod;
  }
  for (int i = 0; i < n; i++) {
    long long val = 0;
    for (int j = 0; j < m; j++) val = (val + ((long long)ans[j] * a[i][j])) % mod;
    if (val != a[i][m]) return -1; //no solution
  }
  return free_var; //has solution
}

void solve() {
  int N, s, e, M;
  cin >> N >> s >> e >> M;

  vector<vector<int>> Q(N + 1, vector<int>(N + 1, -1));
  vector<vector<int>> A(M, vector<int>(200, 0));

  int it = 0;
  vector<int> D(M);
  for (int i = 0; i < M; i++) {
    int p;
    cin >> D[i] >> p;

    vector<int> T(p);
    for (int j = 0; j < p; j++) cin >> T[j];

    for (int j = 0; j < p - 1; j++) {
      int a = T[j], b = T[j + 1];
      if (a > b) swap(a, b);
      if (Q[a][b] == -1) Q[a][b] = it++;
      A[i][Q[a][b]]++;
    }
  }
  for (int i = 0; i < M; i++) {
    A[i].resize(it);
    for (int& e : A[i]) e %= 13;

    A[i].push_back(D[i]);
  }

  vector<int> ans;
  Gauss(A, ans, 13);

  vector<vector<int>> cost(N + 1, vector<int>(N + 1, 1e9));
  for (int i = 1; i <= N; i++) for (int j = i; j <= N; j++) {
    if (i == j) cost[i][j] = cost[j][i] = 0;
    else if (Q[i][j] != -1) cost[i][j] = cost[j][i] = ans[Q[i][j]];
  }

  for (int k = 1; k <= N; k++) for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
    cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
  }

  cout << cost[s][e] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
