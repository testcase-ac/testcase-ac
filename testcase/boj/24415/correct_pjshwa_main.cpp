#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 26;
matrix operator * (const matrix &a, const matrix &b) {
  int n = a.size();
  matrix c(n, vector<ll>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    }
  }
  return c;
}

vector<tuple<string, int, int>> commands;

void solve() {
  int n, c;
  ll k;
  string s;
  cin >> n >> c >> k >> s;

  matrix ans = matrix(n + 1, vector<ll>(n + 1));
  matrix a = matrix(n + 1, vector<ll>(n + 1));

  vector<ll> pos(n + 1), addend(n + 1, 0);
  for (int i = 0; i < n + 1; i++) {
    ans[i][i] = 1;
    pos[i] = i;
  }

  for (int i = 0; i < c; i++) {
    string op;
    int a, b;
    cin >> op >> a >> b;
    commands.push_back(make_tuple(op, a, b));

    if (op == "S") {
      swap(pos[a], pos[b]);
      swap(addend[a], addend[b]);
    }
    if (op == "A") addend[a] = (addend[a] + b) % MOD;
  }

  for (int i = 0; i < n; i++) {
    a[i][pos[i]] = 1;
    a[i][n] = addend[i];
  }
  a[n][n] = 1;

  ll rep = k / c;

  // Exponentiation by squaring
  while (rep) {
    if (rep & 1) ans = ans * a;
    a = a * a;
    rep /= 2;
  }

  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= n; j++) {
      if (j == n) v[i] = (v[i] + ans[i][j]) % MOD;
      else v[i] = (v[i] + ans[i][j] * (s[j] - 'A')) % MOD;
    }
  }

  for (int i = 0; i < n; i++) s[i] = v[i] + 'A';

  for (int i = 0; i < k % c; i++) {
    auto [op, a, b] = commands[i];

    if (op == "S") swap(s[a], s[b]);
    if (op == "A") {
      b %= 26;
      if (s[a] + b > 'Z') s[a] += b - 26;
      else s[a] += b;
    }
  }

  cout << s << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
