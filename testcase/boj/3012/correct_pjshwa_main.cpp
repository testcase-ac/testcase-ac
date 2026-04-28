#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200, MOD = 1e5;
ll dp[MAXN][MAXN], dpo[MAXN][MAXN]; string S, E1 = "([{", E2 = ")]}";
int flag = 0;

pair<ll, int> rec(int l, int r) {
  if (l > r) return {1, 0};
  if (dp[l][r] != -1) return {dp[l][r], dpo[l][r]};

  ll ret = 0, reto = 0;
  for (int i = l + 1; i <= r; i += 2) for (int j = 0; j < 3; j++) {
    if ((S[l] == '?' || S[l] == E1[j]) && (S[i] == '?' || S[i] == E2[j])) {
      auto [lhs, lo] = rec(l + 1, i - 1);
      auto [rhs, ro] = rec(i + 1, r);
      int lz = lhs == 0 && !lo, rz = rhs == 0 && !ro;
      if (lz || rz) continue;

      ret += lhs * rhs;
      reto |= (lo || ro || ret >= MOD);
      ret %= MOD;
    }
  }
  dp[l][r] = ret;
  dpo[l][r] = reto;
  return {dp[l][r], dpo[l][r]};
}

void solve() {
  int N; cin >> N >> S;
  if (N & 1) cout << "0\n";
  else {
    memset(dp, -1, sizeof(dp));
    auto [ret, reto] = rec(0, N - 1);
    string rets = to_string(ret);
    if (reto) while (rets.size() < 5) rets = '0' + rets;
    cout << rets << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
