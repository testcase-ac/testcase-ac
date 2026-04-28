#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
bool vis[MAX + 1];

void solve() {
  string S;
  cin >> S;
  int n = S.size();

  int ans = 0;
  priority_queue<int> bpos;
  for (int i = n - 1; i >= 0; i--) {
    if (S[i] == 'B') bpos.push(i);
    if (S[i] == 'A' && bpos.size()) {
      vis[bpos.top()] = 1;
      bpos.pop();
      ans++;
    }
  }

  priority_queue<int, vector<int>, greater<int>> bpos_inv;
  for (int i = 0; i < n; i++) {
    if (S[i] == 'B' && !vis[i]) bpos_inv.push(i);
    if (S[i] == 'C' && bpos_inv.size()) {
      vis[bpos_inv.top()] = 1;
      bpos_inv.pop();
      ans++;
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
