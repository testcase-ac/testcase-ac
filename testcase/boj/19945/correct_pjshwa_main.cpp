#include <bits/stdc++.h>
typedef unsigned long long ull;
using namespace std;

int main() {
  int n;
  cin >> n;

  if (n < 0) cout << 32;
  else if (n == 0) cout << 1;
  else {
    int pow = 1;
    while (n >= (1 << pow)) pow++;
    cout << pow;
  }
  cout << '\n';
}
