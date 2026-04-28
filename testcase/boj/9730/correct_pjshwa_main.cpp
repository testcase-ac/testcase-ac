#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

stack<int> S;
int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, x, ans = 0; cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> x;
    while (!S.empty() && S.top() < x) {
      S.pop();
      if (S.empty()) ans += x;
      else ans += min(x, S.top());
    }
    S.push(x);
  }

  while (S.size() > 1) {
    S.pop(); ans += S.top();
  }
  S.pop();

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
