#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 19;
const int D[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int C[MOD];

void solve() {
  string S; cin >> S;

  for (int yyyy = 1; yyyy <= 9999; ++yyyy) {
    stringstream ystrs;
    ystrs << setfill('0') << setw(4) << yyyy;
    string ystr = ystrs.str();

    bool ok = 1;
    for (int i = 0; i < 4; ++i) ok &= (ystr[i] == S[i + 4] || S[i + 4] == 'X');
    if (!ok) continue;

    for (int mm = 1; mm <= 12; ++mm) {
      stringstream mstrs;
      mstrs << setfill('0') << setw(2) << mm;
      string mstr = mstrs.str();

      ok = 1;
      for (int i = 0; i < 2; ++i) ok &= (mstr[i] == S[i + 2] || S[i + 2] == 'X');
      if (!ok) continue;

      bool is_leap = (yyyy % 4 == 0 && yyyy % 100 != 0) || (yyyy % 400 == 0);
      int dd = D[mm] + (is_leap && mm == 2);
      for (int d = 1; d <= dd; ++d) {
        stringstream dstrs;
        dstrs << setfill('0') << setw(2) << d;
        string dstr = dstrs.str();

        ok = 1;
        for (int i = 0; i < 2; ++i) ok &= (dstr[i] == S[i] || S[i] == 'X');
        if (!ok) continue;

        vector<char> Zs; int Snum = 0;
        for (int i = 0; i < 2; ++i) Zs.push_back(dstr[i]);
        for (int i = 0; i < 2; ++i) Zs.push_back(mstr[i]);
        for (int i = 0; i < 4; ++i) Zs.push_back(ystr[i]);
        for (int i = 0; i < 8; ++i) Snum = (Snum + (10 - i) * (Zs[i] - '0')) % MOD;
        ++C[Snum];
      }
    }
  }

  S = S.substr(7);
  vector<vector<ll>> dp(11, vector<ll>(MOD, 0));
  for (int j = 0; j < MOD; ++j) dp[0][j] = C[j];
  for (int i = 1; i <= 10; ++i) for (int pj = 0; pj < MOD; ++pj) {
    int coef = i == 1 ? 2 : 12 - i;
    for (int c = 0; c < 10; ++c) {
      if (S[i] != 'X' && S[i] != c + '0') continue;
      int nj = (pj + c * coef) % MOD;
      dp[i][nj] += dp[i - 1][pj];
    }
  }

  auto to_c = [](int Snum) {
    if (Snum <= 9) return Snum;
    else return MOD - Snum;
  };

  ll ans = 0;
  for (int j = 0; j < MOD; ++j) {
    if (S.back() != 'X' && S.back() != to_c(j) + '0') continue;
    ans += dp[10][j];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
