#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  if (n == 3) cout << "NO\n";
  else if (n == 2) cout << "YES\nswap 1 2\nswap 1 2\nswap 1 2\nswap 1 2\nswap 1 2\n";
  else if (k == 1) {
    cout << "YES\n";
    cout << "swap 1 2\n";
    cout << "reverse " << 2 << ' ' << n << '\n';
    cout << "reverse " << 2 << ' ' << n - 1 << '\n';
    cout << "reverse " << 1 << ' ' << n << '\n';
    cout << "reverse " << 1 << ' ' << n << '\n';
  }
  else if (n - k == 1) {
    cout << "YES\n";
    cout << "swap " << n - 1 << ' ' << n << '\n';
    cout << "reverse " << 1 << ' ' << n - 1 << '\n';
    cout << "reverse " << 2 << ' ' << n - 1 << '\n';
    cout << "reverse " << 1 << ' ' << n << '\n';
    cout << "reverse " << 1 << ' ' << n << '\n';
  }
  else {
    cout << "YES\n";
    cout << "reverse " << 1 << ' ' << k << '\n';
    cout << "reverse " << k + 1 << ' ' << n << '\n';
    cout << "reverse " << 1 << ' ' << n << '\n';
    cout << "reverse " << 1 << ' ' << n << '\n';
    cout << "reverse " << 1 << ' ' << n << '\n';
  }
}
