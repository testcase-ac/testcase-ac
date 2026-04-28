#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(false);
}

bool isOperator1(char c) {
  return c == '+' || c == '-';
}

bool isOperator2(char c) {
  return c == '*' || c == '/';
}

int main() {
  fast_io();

  string s;
  cin >> s;
  int sz = s.size();

  stack<char> st;
  string ans = "";
  for (int i = 0; i < sz; i++) {
    if (isOperator1(s[i])) {
      while (!st.empty() && st.top() != '(') {
        ans += st.top();
        st.pop();
      }
      st.push(s[i]);
    }
    else if (isOperator2(s[i])) {
      while (!st.empty() && isOperator2(st.top())) {
        ans += st.top();
        st.pop();
      }
      st.push(s[i]);
    }
    else if (s[i] == '(') st.push(s[i]);
    else if (s[i] == ')') {
      while (!st.empty() && st.top() != '(') {
        ans += st.top();
        st.pop();
      }
      st.pop();
    }
    else ans += s[i];
  }

  while (!st.empty()) {
    ans += st.top();
    st.pop();
  }

  cout << ans;

}
