#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  string s, r;
  int n, k;
  cin >> n >> k >> s;

  stack<char> st;
  for (int i = 0; i < n; i++) {
    while (st.size() > max(0, i - k) && st.top() < s[i]) st.pop();
    st.push(s[i]);
  }
  while (st.size() > n - k) st.pop();
  while (!st.empty()) {
    r += st.top();
    st.pop();
  }
  reverse(r.begin(), r.end());
  cout << r;
}
