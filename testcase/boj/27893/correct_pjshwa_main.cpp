#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; string S; cin >> N >> M >> S;

  deque<int> ps, xs;
  int pc = 0, streak_p = 0, streak_x = 0;
  for (char c : S) {
    if (c == '.') {
      if (streak_x) {
        xs.push_back(streak_x);
        streak_x = 0;
      }
      streak_p++; pc++;
    }
    else {
      if (streak_p) {
        ps.push_back(streak_p);
        streak_p = 0;
      }
      streak_x++;
    }
  }
  if (streak_p) ps.push_back(streak_p);
  if (streak_x) xs.push_back(streak_x);

  int ans = pc;

  if (S[0] == '.') ps.pop_front();
  if (!ps.empty() && S.back() == '.') ps.pop_back();
  for (int x : xs) ans += 2;

  priority_queue<int, vector<int>, greater<int>> pq;
  for (int p : ps) pq.push(p);

  while (!pq.empty() && M >= pq.top()) {
    int t = pq.top(); pq.pop();
    M -= t; ans -= 2 + t;
  }

  if (pc == N) cout << min(ans - M + 2, ans) << '\n';
  else cout << ans - M << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
