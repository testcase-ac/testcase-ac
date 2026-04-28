#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, k;
  string s;
  cin >> n >> k >> s;

  stack<pair<char, int>> stk;

  for (int i = 0; i < n; i++) {
    if (!stk.empty() && s[i] == stk.top().first) stk.push({s[i], stk.top().second + 1});
    else stk.push({s[i], 1});

    if (stk.top().second == k) {
      for (int j = 0; j < k; j++) stk.pop();
    }
  }

  vector<char> ans;
  while (!stk.empty()) {
    ans.push_back(stk.top().first);
    stk.pop();
  }
  reverse(ans.begin(), ans.end());
  for (char c : ans) cout << c;
}
