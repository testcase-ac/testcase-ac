#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool vis[1000000][11];

int main() {
  fast_io();

  string s;
  int n, k;
  cin >> s >> k;
  if (s == "1000000") return cout << s, 0;

  n = s.size();
  int ans = -1;

  queue<pair<string, int>> q;
  q.push({s, 0});

  while (!q.empty()) {
    auto [cs, step] = q.front();
    q.pop();

    int ci = stoi(cs);

    if (vis[ci][step]) continue;
    vis[ci][step] = true;

    if (step == k) {
      ans = max(ans, ci);
      continue;
    }

    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        if (i == 0 && cs[j] == '0') continue;
        string ns = cs;
        swap(ns[i], ns[j]);
        if (!vis[stoi(ns)][step + 1]) q.push({ns, step + 1});
      }
    }

  }
  
  cout << ans;
}
