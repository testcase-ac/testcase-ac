#include <bits/stdc++.h>
using namespace std;

int main() {
  string s, f = "PPAP", r;
  cin >> s;

  for (int i = 0; i < s.size(); i++) {
    r += s[i];
    if (r.size() >= f.size() && r.substr(r.size() - f.size()) == f) r.resize(r.size() - f.size() + 1);
  }
  cout << (r == "P" ? "PPAP" : "NP") << '\n';
}
