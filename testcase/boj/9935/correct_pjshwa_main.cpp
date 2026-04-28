#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
  string s, f;
  cin >> s >> f;

  stack<pair<char, int>> fn;
  fn.push({';', -1});

  int ssz = s.size(), fsz = f.size(), fidx;
  for (int i = 0; i < ssz; i++) {
    fidx = fn.top().second + 1;
    if (s[i] == f[fidx]) {
      fn.push({s[i], fidx});
      if (fidx == fsz - 1) {
        for (int j = 0; j < fsz; j++) fn.pop();
      }
    }
    else if (s[i] == f[0]) fn.push({s[i], 0});
    else fn.push({s[i], -1});
  }

  vector<char> ans;
  while (!fn.empty()) {
    ans.push_back(fn.top().first);
    fn.pop();
  }
  ans.pop_back(); // dummy character
  reverse(ans.begin(), ans.end());

  if (ans.empty()) cout << "FRULA";
  else for (auto el : ans) cout << el;
  cout << '\n';
}
