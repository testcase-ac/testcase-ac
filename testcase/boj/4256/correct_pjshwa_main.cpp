#include <iostream>
using namespace std;

const int MAX = 1000;
int s[MAX], t[MAX];

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
  cout << s[ps] << ' ';
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> s[i];
  for (int i = 0; i < n; i++) cin >> t[i];
  print_next(0, n - 1, 0, n - 1);
  cout << '\n';
}

int main() {
  fast_io();

  int tt;
  cin >> tt;
  while (tt--) solve();
}
