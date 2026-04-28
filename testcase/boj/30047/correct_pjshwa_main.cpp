#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  reverse(S.begin(), S.end());

  stack<int> st;
  for (char c : S) {
    if (c == 'x') st.push(0);
    else if (c == 'g') {
      if (st.empty()) return cout << "-1\n", void();
      int t = st.top(); st.pop();
      st.push(t + 1);
    }
    else {
      if (st.size() < 2) return cout << "-1\n", void();
      int t1 = st.top(); st.pop();
      int t2 = st.top(); st.pop();
      st.push(min(t1, t2));
    }
  }

  if (st.size() == 1) cout << st.top() << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
