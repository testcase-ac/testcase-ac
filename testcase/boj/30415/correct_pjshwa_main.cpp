#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;
vector<ll> P, cur, opt;
int m, Z;
ll opt_sum = INF;

// i-th prime power can choose AT MOST one slot to NOT be placed in
void dfs(int i) {
  if (i == Z) {
    ll cur_sum = accumulate(cur.begin(), cur.end(), 0LL);
    if (cur_sum < opt_sum) {
      opt_sum = cur_sum;
      opt = cur;
    }
    return;
  }

  for (int j = 0; j < m; ++j) cur[j] *= P[i];
  dfs(i + 1);
  for (int j = 0; j < m; ++j) cur[j] /= P[i];

  for (int l = 0; l < m; ++l) {
    for (int j = 0; j < m; ++j) {
      if (j == l) continue;
      cur[j] *= P[i];
    }
    dfs(i + 1);
    for (int j = 0; j < m; ++j) {
      if (j == l) continue;
      cur[j] /= P[i];
    }
  }
}

void solve() {
  int n; cin >> n >> m;

  int on = n;
  for (int i = 2; i <= on; ++i) {
    if (n % i) continue;

    int u = 1;
    while (n % i == 0) {
      n /= i;
      u *= i;
    }
    P.push_back(u);
  }

  Z = P.size();
  if (Z < m) return cout << "-1\n", void();

  cur.resize(Z, 1);
  dfs(0);

  if (opt_sum == INF) cout << "-1\n";
  else {
    for (int i = 0; i < m; ++i) {
      cout << opt[i] << " \n"[i == m - 1];
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
