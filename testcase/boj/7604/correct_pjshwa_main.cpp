#include <bits/stdc++.h>
using namespace std;

int n;
string s, t;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<char> ans;

// preorder tree range, inorder tree range
void find_next(int ps, int pe, int is, int ie) {
  // Find root position in inorder array
  int pos = is;
  if (ps >= n || pos >= n) return;

  while (pos < n && t[pos] != s[ps]) pos++;

  if (pos > is) find_next(ps + 1, ps + pos - is, is, pos - 1);
  if (pos < ie) find_next(ps + pos - is + 1, pe, pos + 1, ie);
  ans.push_back(s[ps]);
}

int main() {
  fast_io();

  while (cin >> s) {
    if (s == "#") break;
    cin >> t;

    n = s.size();
    ans.clear();
    find_next(0, n - 1, 0, n - 1);

    if (ans.size() == n) {
      for (char c : ans) cout << c;
    }
    else cout << "Invalid tree";
    cout << '\n';
  }
}
