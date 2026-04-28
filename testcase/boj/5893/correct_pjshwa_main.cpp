#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  string s;
  cin >> s;

  string r = s + "0000";

  bool carry = false;
  for (int i = r.size() - 1; i >= 0; i--) {
    int a = i >= 4 ? s[i - 4] - '0' : 0;
    int b = r[i] - '0';
    int c = a + b + carry;
    carry = c / 2;
    r[i] = c % 2 + '0';
  }
  if (carry) cout << 1;
  cout << r << '\n';
}
