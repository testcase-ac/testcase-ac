#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n / 2; i++) cout << "1 2 ";
  if (n & 1) cout << "3";
}
