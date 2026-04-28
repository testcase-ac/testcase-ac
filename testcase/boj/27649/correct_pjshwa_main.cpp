#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_separator(char c) {
  return c == '<' || c == '>' || c == '&' || c == '|' || c == '(' || c == ')' || c == ' ';
}

void solve() {
  string S; getline(cin, S);

  vector<string> T;
  string R = "";
  for (char c : S) {
    if (is_separator(c)) {
      if (c == '&') {
        if (R != "&") {
          if (R != "") T.push_back(R);
          R = "&";
        }
        else {
          R += c;
          T.push_back(R), R = "";
        }
      }
      else if (c == '|') {
        if (R != "|") {
          if (R != "") T.push_back(R);
          R = "|";
        }
        else {
          R += c;
          T.push_back(R), R = "";
        }
      }
      else if (c == ' ') {
        if (R != "") T.push_back(R);
        R = "";
      }
      else {
        if (R != "") T.push_back(R);
        T.push_back(string(1, c));
        R = "";
      }
    }
    else R += c;
  }
  if (R != "") T.push_back(R);

  for (string s : T) cout << s << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
