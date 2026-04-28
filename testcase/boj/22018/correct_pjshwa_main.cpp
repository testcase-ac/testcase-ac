#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, D;
  cin >> N >> M >> D;

  vector<pii> A(N);
  for (auto& [x, v] : A) cin >> x >> v;
  sort(A.begin(), A.end());

  int left = 1, right = 1e9 + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    
    vector<int> B;
    for (auto& [x, v] : A) if (v >= mid) B.push_back(x);

    int z = B.size();
    vector<int> dp(z);
    for (int i = 0; i < z; i++) {
      if (i) dp[i] = dp[i - 1];

      auto it = upper_bound(B.begin(), B.end(), B[i] - D);

      if (it == B.begin()) dp[i] = max(dp[i], 1);
      else dp[i] = max(dp[i], dp[it - B.begin() - 1] + 1);
    }

    if (z >= M && dp[z - 1] >= M) left = mid + 1;
    else right = mid;
  }

  if (left == 1) cout << "-1\n";
  else cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
