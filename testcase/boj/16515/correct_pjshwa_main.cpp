#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
  int n;
  cin >> n;

  ll denom = 1;
  double e = 1;
  for (int i = 1; i <= min(16, n); i++) {
    denom *= i;
    e += (double)1 / denom;
  }
  cout << fixed << setprecision(15) << e << '\n';
}
