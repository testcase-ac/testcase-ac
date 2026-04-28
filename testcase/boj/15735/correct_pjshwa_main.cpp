#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
  ll n, k;
  cin >> n;

  ll s = n * (n + 1) * (n + 2) / 6;

  k = n / 2;
  if (n % 2 == 0) s += (k * (k + 1) * (4 * k - 1) / 6);
  else s += (k * (k + 1) * (4 * k + 5) / 6);

  cout << s << '\n';
}
