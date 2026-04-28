#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  priority_queue<int> pq; ll ans = 0;
  for (int i = 0; i < N; ++i) {
    int c; cin >> c;
    if (S[i] == '(') pq.push(c);
    else {
      if (!pq.empty() && pq.top() + c > 0) {
        ans += pq.top() + c; pq.pop();
        pq.push(-c);
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
