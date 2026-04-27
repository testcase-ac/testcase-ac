#include <iostream>
#include <algorithm>

using namespace std;

int L, R, S;

void exe(int tc) {
  cin >> L >> R >> S;

  cout << min(2 * (R - S), 2 * (S - L) + 1) << '\n';
}

int main() {
  int tc;
  cin >> tc;
  for (int i = 1; i <= tc; i++) exe(i);
}