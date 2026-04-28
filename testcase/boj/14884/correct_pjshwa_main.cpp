#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 10000007;
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

void solve() {
  ll N, K; cin >> N >> K;

  int flag = K > 0; K = max(K, 1LL);
  int L = K * 4;
  matrix ans = matrix(L, vector<ll>(L));
  matrix a = matrix(L, vector<ll>(L));

  auto get_state = [&](int as, int bs, int cs) {
    return as * 4 + bs * 2 + cs;
  };

  for (int as = 0; as < K; ++as) for (int bs = 0; bs < 2; ++bs) for (int cs = 0; cs < 2; ++cs) {
    int state = get_state(as, bs, cs), nstate;
    ans[state][state] = 1;

    // A solves the problem
    if (flag) {
      nstate = get_state((as + 1) % K, 0, cs);
      a[nstate][state] = (a[nstate][state] + 1) % MOD;
    }

    // B solves the problem
    if (bs == 0) {
      nstate = get_state(as, 1, cs);
      a[nstate][state] = (a[nstate][state] + 1) % MOD;
    }

    // C solves the problem
    nstate = get_state(as, 0, 1);
    a[nstate][state] = (a[nstate][state] + 1) % MOD;
  }

  while (N) {
    if (N & 1) ans = ans * a;
    a = a * a;
    N /= 2;
  }

  vector<int> states = {
    get_state(0, 0, 1),
    get_state(0, 1, 1)
  };

  ll result = 0;
  for (int state : states) {
    result = (result + ans[state][0]) % MOD;
  }
  cout << result << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
