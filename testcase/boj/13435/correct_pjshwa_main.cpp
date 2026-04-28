#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  if (n > m) swap(n, m);

  if (n == 1 || n == m) {
    cout << m;
    return 0;
  }

  n--; m--;
  ll g = __gcd(n, m);
  cout << (2 * n - (n / g) + 1) * (m / g - 1) / 2 + n + 1;
}
