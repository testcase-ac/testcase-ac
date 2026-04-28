#include <iostream>

using namespace std;

void print_stars(int n) {
  if (n == 0) return;

  for (int i = 0; i < n; i++) {
    cout << string(n - i, ' ') << '*';

    if (i >= 1) cout << string(2 * i - 1, ' ') << '*';
    cout << '\n';
  }
}

int main() {
  int n;
  cin >> n;

  print_stars(n - 1);
  cout << string(2 * n - 1, '*') << '\n';
}
