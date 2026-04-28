#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
string S[MAXN + 1];
int E[MAXN + 1], P[MAXN + 1], V[MAXN + 1];

void solve() {
  int Ta, Tb, Va, Vb; cin >> Ta >> Tb >> Va >> Vb;

  int ans = INT_MAX;
  for (int e = 0; e <= Va; ++e) {
    int dT = Tb * Vb + Ta * e;
    int sT = Ta * (Va - e);
    ans = min(ans, max(dT, sT));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
