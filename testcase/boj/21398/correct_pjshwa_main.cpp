#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool albert_score(char c) {
  return c == 'A' || c == 'L' || c == 'B' || c == 'E' || c == 'R' || c == 'T';
}

bool alice_score(char c) {
  return c == 'A' || c == 'L' || c == 'I' || c == 'C' || c == 'E';
}

const int MAXN = 150, MAXS = 300, BIAS = 150;
bool dp[MAXN + 1][MAXN + 1][MAXS + 1];

void solve() {
  string S; cin >> S;
  int N = S.size();

  for (int turn = 0; turn <= N; ++turn) for (int l = 0; l <= turn; ++l) for (int s = 0; s <= MAXS; ++s) {
    dp[turn][l][s] = false;
  }
  dp[0][0][BIAS] = true;

  for (int turn = 0; turn < N; ++turn) {
    if (turn % 2 == 0) {
      // Albert turn
      for (int l = 0; l <= turn; ++l) for (int s = 0; s <= MAXS; ++s) {
        int li = l, ri = N - 1 - turn + l;
        if (li == ri) {
          int bonus = albert_score(S[li]) ? 2 : 0;
          if (s + bonus <= MAXS) dp[turn + 1][l + 1][s + bonus] |= dp[turn][l][s];
        }
        else {
          char cl = S[li], cr = S[ri];
          if (albert_score(cl)) {
            if (s + 2 <= MAXS) dp[turn + 1][l + 1][s + 2] |= dp[turn][l][s];
          }
          else {
            int bonus = albert_score(cr) ? 2 : 0;
            if (s + bonus <= MAXS) dp[turn + 1][l][s + bonus] |= dp[turn][l][s];
          }
        }
      }
    }
    else {
      // Alice turn
      for (int l = 0; l <= turn; ++l) for (int s = 0; s <= MAXS; ++s) {
        int li = l, ri = N - 1 - turn + l;

        // either take left or right
        if (alice_score(S[li])) {
          if (s - 1 >= 0) dp[turn + 1][l + 1][s - 1] |= dp[turn][l][s];
        }
        else {
          dp[turn + 1][l + 1][s] |= dp[turn][l][s];
        }

        if (alice_score(S[ri])) {
          if (s - 1 >= 0) dp[turn + 1][l][s - 1] |= dp[turn][l][s];
        }
        else {
          dp[turn + 1][l][s] |= dp[turn][l][s];
        }
      }
    }
  }

  int ans = MAXS + 1;
  for (int l = 0; l <= N; ++l) for (int s = BIAS + 1; s <= MAXS; ++s) {
    if (dp[N][l][s]) ans = min(ans, abs(s - BIAS));
  }
  if (ans == MAXS + 1) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
