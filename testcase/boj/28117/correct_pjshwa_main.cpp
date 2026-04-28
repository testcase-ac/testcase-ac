#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 20;
ll F[MAX + 1];

void solve() {
  int N; string S; cin >> N >> S;

  int streak = 0, i = 0;
  vector<int> ss;

  // Find streaks of `long`
  while (i < N) {
    if (S.substr(i, 4) == "long") {
      streak++;
      i += 4;
    }
    else {
      if (streak) ss.push_back(streak);
      streak = 0;
      i++;
    }
  }
  if (streak) ss.push_back(streak);

  ll ans = 1;
  for (int s : ss) ans *= F[s];
  cout << ans << '\n';
}

int main() {
  fast_io();

  F[0] = F[1] = 1;
  for (int i = 2; i <= MAX; i++) F[i] = F[i - 1] + F[i - 2];

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
