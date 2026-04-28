#include <iostream>

using namespace std;

int inorder[100000];
int postorder[100000];

// inorder tree range, postorder tree range
void print_next(int is, int ie, int ps, int pe) {
  cout << postorder[pe] << ' ';

  // Find root position in inorder array
  int pos = is;
  while (inorder[pos] != postorder[pe]) pos++;

  if (pos > is) print_next(is, pos - 1, ps, pos - (is - ps) - 1);
  if (pos < ie) print_next(pos + 1, ie, pos - (is - ps), pe - 1);
}

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> inorder[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> postorder[i];
  }

  print_next(0, n - 1, 0, n - 1);
  cout << '\n';
}
