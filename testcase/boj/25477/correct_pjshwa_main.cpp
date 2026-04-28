#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N;
  cin >> N;

  vector<int> ans(N, -1);
  ll sum = 0;
  priority_queue<pii> pq;
  for (int i = 0; i < N; i++) {
    string op;
    cin >> op;
    if (op == "UBACI") {
      int x;
      cin >> x;
      pq.push({x, i});
      ans[i] = 0;
    }
    else {
      auto [x, j] = pq.top();
      pq.pop();

      ans[j] = 1;
      sum += x;
    }
  }

  cout << sum << '\n';
  for (int i = 0; i < N; i++) {
    if (ans[i] == -1) continue;
    cout << (ans[i] == 1 ? 'P' : 'K');
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
