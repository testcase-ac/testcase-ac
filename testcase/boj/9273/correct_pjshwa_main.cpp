#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string S;
void solve() {
  int n = stoi(S.substr(2));

  ll tw = 1;
  for (int i = 2; i * i <= n; i++) {
    int w = 0;
    while (n % i == 0) {
      n /= i;
      w++;
    }
    tw *= (2 * w + 1);
  }
  if (n > 1) tw *= 3;

  cout << (tw + 1) / 2 << '\n';
}

int main() {
  fast_io();

  while (cin >> S) solve();
}
