#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  // if S contains '*'
  if (S.find('*') != string::npos) {
    {
      int acc = 0;
      for (int i = 0; i < N; ++i) {
        if (S[i] == '*') break;
        if (S[i] == ')') --acc;
        else ++acc;
        if (acc < 0) return cout << "NO\n", void();
      }
    }
    {
      int acc = 0;
      for (int i = N - 1; i >= 0; --i) {
        if (S[i] == '*') break;
        if (S[i] == '(') --acc;
        else ++acc;
        if (acc < 0) return cout << "NO\n", void();
      }
    }
    return cout << "YES\n", void();
  }

  int oc = 0;
  for (char c : S) if (c == '(') ++oc;

  int H = N / 2;
  for (int i = 0; i < N; ++i) {
    if (S[i] != '?') continue;

    if (oc < H) S[i] = '(', ++oc;
    else S[i] = ')';
  }

  stack<char> st;
  for (char c : S) {
    if (c == '(') st.push(c);
    else {
      if (st.empty()) return cout << "NO\n", void();
      st.pop();
    }
  }

  if (st.empty()) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
