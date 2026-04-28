#include <iostream>

using namespace std;

string s, t;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

// preorder tree range, inorder tree range
void print_next(int ps, int pe, int is, int ie) {
  // Find root position in inorder array
  int pos = is;
  while (t[pos] != s[ps]) pos++;

  if (pos > is) print_next(ps + 1, ps + pos - is, is, pos - 1);
  if (pos < ie) print_next(ps + pos - is + 1, pe, pos + 1, ie);
  cout << s[ps];
}

int main() {
  fast_io();

  while (cin >> s >> t) {
    int n = s.size();
    print_next(0, n - 1, 0, n - 1);
    cout << '\n';
  }
}
