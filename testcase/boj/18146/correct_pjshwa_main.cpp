#include <bits/stdc++.h>
using namespace std;

int main() {
  long long t, n;
  cin >> t;

  while (t--) {
    cin >> n;
    cout << ((n * n + n) ^ (n + 1)) << '\n';
  }
}
