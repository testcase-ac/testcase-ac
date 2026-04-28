#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char seq[2500];
bool seq_p[2500][2500];
int scomb_dp[2500];

int scomb(int idx) {
  if (idx == -1) return 0;
  if (scomb_dp[idx] == -1) {
    int min_v = 2501, sp = idx;
    while (sp >= 0) {
      if (seq_p[sp][idx]) min_v = min(min_v, scomb(sp - 1));
      sp--;
    }
    scomb_dp[idx] = 1 + min_v;
  }
  return scomb_dp[idx];
}

int main() {
  fast_io();

  memset(scomb_dp, -1, sizeof(scomb_dp));

  cin >> seq;
  int n = strlen(seq);

  for (int i = 0; i < n; i++) seq_p[i][i] = true;
  for (int i = 0; i < n - 1; i++) {
    seq_p[i][i + 1] = seq[i] == seq[i + 1];
  }
  for (int diff = 2; diff < n; diff++) {
    for (int i = 0; i < n - diff; i++) {
      int j = i + diff;
      seq_p[i][j] = (seq[i] == seq[j] && seq_p[i + 1][j - 1]);
    }
  }

  cout << scomb(n - 1) << '\n';
}
