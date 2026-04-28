#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool ask(int l, int r) {
  cout << "? " << l << ' ' << r << endl;
  string s;
  cin >> s;
  return s == "Yes";
}

void solve() {
  int n;
  cin >> n;

  stack<int> p; vector<char> ans;
  for (int i = 1; i <= n; i++) {
    if (p.empty()) {
      p.push(i);
      ans.push_back('(');
      continue;
    }

    if (ask(p.top(), i)) {
      p.pop();
      ans.push_back(')');
    }
    else {
      p.push(i);
      ans.push_back('(');
    }
  }

  cout << "! " << string(ans.begin(), ans.end()) << endl;
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
