#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  priority_queue<int> L, R;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    if (x < 0) L.push(-x);
    else R.push(x);
  }

  vector<int> moves;
  while (!L.empty()) {
    int cur = 0;
    for (int i = 0; i < M; i++) {
      if (L.empty()) break;
      cur = max(cur, L.top());
      L.pop();
    }
    moves.push_back(cur);
  }
  while (!R.empty()) {
    int cur = 0;
    for (int i = 0; i < M; i++) {
      if (R.empty()) break;
      cur = max(cur, R.top());
      R.pop();
    }
    moves.push_back(cur);
  }

  sort(moves.begin(), moves.end(), greater<int>());
  int ans = reduce(moves.begin(), moves.end());
  for (int i = 1; i < moves.size(); i++) ans += moves[i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
