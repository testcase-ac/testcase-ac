#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500, MAXA = 180;
bool dp[MAXN + 1][MAXN / 2 + 1][MAXA];
int A[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  if (N & 1) return cout << "NO\n", void();

  dp[0][0][0] = true;
  for (int i = 1; i <= N; ++i) for (int pc = 0; pc <= N / 2; ++pc) {
    for (int pa = 0; pa < MAXA; ++pa) {
      dp[i][pc][(pa - A[i] + MAXA) % MAXA] |= dp[i - 1][pc][pa];
      if (pc == N / 2) continue;
      dp[i][pc + 1][(pa + A[i]) % MAXA] |= dp[i - 1][pc][pa];
    }
  }

  if (dp[N][N / 2][0]) {
    cout << "YES\n";
    int cc = N / 2, ca = 0, i = N;
    vector<int> sgn(N + 1);
    while (i > 0) {
      if (cc > 0 && dp[i - 1][cc - 1][(ca - A[i] + MAXA) % MAXA]) {
        sgn[i] = -1;
        --cc;
        ca = (ca - A[i] + MAXA) % MAXA;
      } else {
        sgn[i] = 1;
        ca = (ca + A[i]) % MAXA;
      }
      --i;
    }

    vector<int> pos, neg;
    for (int i = 1; i <= N; ++i) {
      if (sgn[i] == 1) pos.push_back(i);
      else neg.push_back(i);
    }
    for (int i = 1; i <= N; ++i) {
      if (i & 1) cout << neg.back() << " ", neg.pop_back();
      else cout << pos.back() << " ", pos.pop_back();
    }

  } else {
    cout << "NO\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
