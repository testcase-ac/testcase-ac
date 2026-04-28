#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int a, b, c;
  cin >> a >> b >> c;

  if (a + b == c) return cout << a << '+' << b << '=' << c << '\n', 0;
  if (a - b == c) return cout << a << '-' << b << '=' << c << '\n', 0;
  if (a * b == c) return cout << a << '*' << b << '=' << c << '\n', 0;
  if (a == b * c) return cout << a << '/' << b << '=' << c << '\n', 0;
  if (a == b + c) return cout << a << '=' << b << '+' << c << '\n', 0;
  if (a == b - c) return cout << a << '=' << b << '-' << c << '\n', 0;
  if (a == b * c) return cout << a << '=' << b << '*' << c << '\n', 0;
  if (a * c == b) return cout << a << '=' << b << '/' << c << '\n', 0;
}
