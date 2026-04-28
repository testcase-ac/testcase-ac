#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  
  queue<int> q;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    q.push(x);
  }

  int cur = 1;
  stack<int> u;
  while (!q.empty()) {
    if (q.front() == cur) {
      q.pop();
      cur++;
    }
    else if (!u.empty() && u.top() == cur) {
      u.pop();
      cur++;
    }
    else {
      u.push(q.front());
      q.pop();
    }
  }

  while (!u.empty()) {
    if (u.top() == cur) {
      u.pop();
      cur++;
    }
    else return cout << "Sad\n", void();
  }

  cout << "Nice\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
