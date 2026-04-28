#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k, t;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    cout << !((n - k) & ((k - 1) / 2)) << '\n';
  }
}
