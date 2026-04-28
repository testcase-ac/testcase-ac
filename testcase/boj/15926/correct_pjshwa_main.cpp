#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  string s;
  cin >> n >> s;

  stack<int> t;
  t.push(-1);

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '(') t.push(i);
    else {
      t.pop();
      if (t.empty()) t.push(i);
      else ans = max(ans, i - t.top());
    }
  }

  cout << ans << '\n';
}
