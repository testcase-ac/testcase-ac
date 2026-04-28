#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int main() {
  fast_io();

  string S;
  cin >> S;
  bool flag = false;
  int L = 0, R = 0;
  for (char& c : S) {
    if (c == '^') flag = true;

    if (c == '@') {
      if (flag) R++;
      else L++;
    }
  }

  cout << L << ' ' << R << '\n';
}
