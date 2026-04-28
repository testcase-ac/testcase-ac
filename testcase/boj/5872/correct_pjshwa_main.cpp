#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  string s;
  cin >> s;
  stack<char> st;

  int chg = 0;
  for (char c : s) {
    if (c == '(') st.push(c);
    else {
      if (st.empty()) {
        chg++;
        st.push('(');
      }
      else st.pop();
    }
  }

  cout << chg + st.size() / 2 << '\n';
}
