#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
set<int> xreach[MAX + 1];
bool xvis[MAX + 1];

int main() {
  fast_io();

  int n, a, b;
  cin >> n >> a >> b;

  queue<pair<int, int>> xq;
  xq.push({a, 0});

  while (!xq.empty()) {
    auto [c, d] = xq.front();
    xq.pop();
    xreach[c].insert(d);

    int s = 1 << d;
    if (c - s > 0) xq.push({c - s, d + 1});
    if (c + s <= n) xq.push({c + s, d + 1});
  }

  queue<pair<int, int>> yq;
  yq.push({b, 0});

  while (!yq.empty()) {
    auto [c, d] = yq.front();
    yq.pop();

    if (xreach[c].count(d)) return cout << d << '\n', 0;

    int s = 1 << d;
    if (c - s > 0) yq.push({c - s, d + 1});
    if (c + s <= n) yq.push({c + s, d + 1});
  }

  cout << "-1\n";
}
