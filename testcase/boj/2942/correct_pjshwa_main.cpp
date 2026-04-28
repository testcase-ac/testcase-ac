#include <bits/stdc++.h>
using namespace std;

vector<int> factors(int k) {
  vector<int> res;
  for (int i = 1; i * i <= k; i++) {
    if (k % i == 0) {
      res.push_back(i);
      if (i * i != k) res.push_back(k / i);
    }
  }
  return res;
}

int main() {
  int a, b;
  cin >> a >> b;

  int g = __gcd(a, b);
  for (int f : factors(g)) {
    cout << f << ' ' << a / f << ' ' << b / f << '\n';
  }
}
