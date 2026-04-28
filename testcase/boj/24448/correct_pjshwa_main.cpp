#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int q;
  cin >> q;
  stack<string> st;
  while (q--) {
    string op;
    cin >> op;
    if (op == "READ") {
      cout << st.top() << '\n';
      st.pop();
    }
    else st.push(op);
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
