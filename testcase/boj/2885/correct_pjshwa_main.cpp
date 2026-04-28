#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, pw = 1;
  cin >> n;
  while (pw < n) pw *= 2;
  cout << pw << ' ';

  int cut = 0;
  while (n) {
    while (pw > n) {
      pw /= 2;
      cut++;
    }
    n -= pw;
  }
  cout << cut << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
