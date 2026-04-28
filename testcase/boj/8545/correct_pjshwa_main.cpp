#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  string S;
  cin >> S;
  reverse(S.begin(), S.end());
  cout << S << '\n';
}
