#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<pair<string, int>> O[70];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    string S; int W, D, P; cin >> S >> W >> D >> P;
    O[(W - 1) * 7 + D].emplace_back(S, P);
  }

  map<string, int> R;
  for (int i = 0; i < N; ++i) {
    string S; int M; cin >> S >> M;
    R[S] = M;
  }

  int streak = 0, max_streak = 0, ldate = -2;
  for (int d = 0; d < 70; ++d) {
    int ok = 0;
    for (auto& [S, P] : O[d]) {
      if (R[S] >= P) ok = 1;
    }
    if (!ok) continue;

    if (ldate + 1 == d) ++streak;
    else streak = 1;

    max_streak = max(max_streak, streak);
    ldate = d;
  }
  cout << max_streak << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
