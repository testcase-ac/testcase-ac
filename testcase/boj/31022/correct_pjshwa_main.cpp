#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 75, INF = 0x3f3f3f3f;
int N, dp[MAXN + 1][MAXN + 1]; string S;

bool validate_score(string& S) {
  if (S == "0") return true;
  if (S[0] == '0') return false;
  if (S.size() == 3 && S != "100") return false;
  return true;
}

void solve() {
  int G; cin >> G >> S;
  N = S.size();

  for (int i = 0; i <= N; ++i) for (int g = 0; g <= G; ++g) dp[i][g] = -INF;
  dp[0][0] = 0;

  for (int i = 0; i < N; ++i) for (int g = 0; g < G; ++g) for (int c = 1; c <= 3; ++c) {
    string Us = S.substr(i, c);
    if (i + c > N || !validate_score(Us)) continue;
    int U = stoi(Us), j = i + c;
    dp[j][g + 1] = max(dp[j][g + 1], dp[i][g] + U);
  }

  cout << (int)round(dp[N][G] / (double)G) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
