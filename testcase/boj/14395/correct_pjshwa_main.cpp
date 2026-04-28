#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int s, t;
  cin >> s >> t;

  if (s == t) return cout << 0, 0;

  queue<pair<ll, string>> q;
  q.push({s, ""});

  while (!q.empty()) {
    auto [c, ops] = q.front();
    q.pop();

    if (c > 1e9) continue;
    if (c == t) return cout << ops, 0;

    if (c > 1) q.push({c * c, ops + '*'});
    q.push({c * 2, ops + '+'});
    if (ops.size() == 0) q.push({1, "/"});
  }

  cout << -1;
}
