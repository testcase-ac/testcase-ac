#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  int p[10];
  for (int i = 0; i < 10; i++) p[i] = i;

  do {
    if (p[2] == 0 || p[6] == 0) continue;

    string a = "", b = "";
    a += (p[2] + '0'), a += (p[1] + '0'), a += (p[3] + '0'), a += (p[3] + '0'), a += (p[4] + '0');
    b += (p[6] + '0'), b += (p[4] + '0'), b += (p[5] + '0'), b += (p[3] + '0'), b += (p[0] + '0');

    if (stoi(a) + stoi(b) == n) {
      cout << "  " << a << '\n';
      cout << "+ " << b << '\n';
      cout << "-------\n";
      cout << setw(7) << n << '\n';
      return;
    }
  } while (next_permutation(p, p + 10));

  cout << "No Answer\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
