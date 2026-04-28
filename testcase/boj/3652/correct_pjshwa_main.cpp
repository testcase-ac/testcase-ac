#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
  ll a, b, tmp;
  scanf("%lld/%lld", &a, &b);

  while (a != b) {
    if (a < b) {
      cout << 'L';
      tmp = a;
      a = b - a;
      b = tmp;
    }
    else {
      cout << 'R';
      tmp = b;
      b = a - b;
      a = tmp;
    }
  }

  cout << '\n';
}
