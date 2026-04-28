#include <bits/stdc++.h>
using namespace std;

int main() {
  string s, f, r;
  cin >> s >> f;

  for (int i = 0; i < s.size(); i++) {
    r += s[i];
    if (r.size() >= f.size() && r.substr(r.size() - f.size()) == f) r.resize(r.size() - f.size());
  }
  cout << r;
}
