#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e6;
int lp[MAX + 1];
vector<int> pr;

void solve() {
  int n, q;
  cin >> n >> q;

  map<int, int> f;
  while (q--) {
    int ai, bi;
    cin >> ai >> bi;
    f.clear();

    while (ai > 1) f[lp[ai]]++, ai /= lp[ai];
    while (bi > 1) f[lp[bi]]++, bi /= lp[bi];

    ll ans = 1;
    for (auto& [k, v] : f) {
      for (int i = 0; i < v / 2; i++) ans *= k;
    }
    cout << ans << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  for (int i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=MAX; ++j)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
