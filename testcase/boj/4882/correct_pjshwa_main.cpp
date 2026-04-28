#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string s;
int tc;

void solve() {
  int n = s.size(), mdepth = 0, cdepth = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '(') cdepth++;
    if (s[i] == ')') cdepth--;
    mdepth = max(mdepth, cdepth);
  }

  stack<int> st;
  for (int i = 0; i < n; i++) {
    if (s[i] == '(') cdepth++, st.push(2);
    if (s[i] == 'T') st.push(1);
    if (s[i] == 'F') st.push(0);
    if (s[i] == ')') {
      int t = st.top();
      st.pop();

      while (st.top() != 2) {
        if ((mdepth - cdepth) & 1) t |= st.top();
        else t &= st.top();
        st.pop();
      }

      st.pop();
      st.push(t);
      cdepth--;
    }
  }

  string res = st.top() ? "true" : "false";
  cout << ++tc << ". " << res << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> s;
    if (s == "()") break;
    solve();
  }
}
