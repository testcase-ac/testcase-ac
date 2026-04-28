#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  queue<int> q;
  while (1) {
    int x;
    cin >> x;
    if (x == -1) break;

    if (x == 0) q.pop();
    else {
      if (q.size() == N) continue;
      q.push(x);
    }
  }

  if (q.empty()) cout << "empty\n";
  else {
    while (!q.empty()) {
      cout << q.front() << ' ';
      q.pop();
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
