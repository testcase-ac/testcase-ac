#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  string S, P; cin >> S >> P;
  int sz = S.size(), pz = P.size();

  vector<int> adv(pz);
  for (int i = 0; i < pz; i++) {
    int k = 0;
    for (int j = 0; j < sz; j++) {
      if (S[j] == P[i + k]) k++;
      else if (S[j] == P[i]) k = 1;
      else k = 0;

      adv[i] = max(adv[i], k);
    }
  }

  vector<int> dp(pz + 1, INF); dp[pz] = 0;
  for (int i = pz - 1; i >= 0; i--) {
    for (int j = 1; j <= adv[i]; j++) {
      dp[i] = min(dp[i], dp[i + j] + 1);
    }
  }
  cout << dp[0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
