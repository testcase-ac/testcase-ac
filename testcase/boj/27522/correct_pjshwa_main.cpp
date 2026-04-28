#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  vector<pair<string, string>> A;
  for (int i = 0; i < 8; i++) {
    string T, D; cin >> T >> D;
    A.push_back({T, D});
  }
  sort(A.begin(), A.end());

  int scores[8] = {10, 8, 6, 5, 4, 3, 2, 1};
  int score_t1 = 0, score_t2 = 0;
  for (int i = 0; i < 8; i++) {
    if (A[i].second == "R") score_t1 += scores[i];
    else score_t2 += scores[i];
  }

  if (score_t1 > score_t2) cout << "Red\n";
  else cout << "Blue\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
