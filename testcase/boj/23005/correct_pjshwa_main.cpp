#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool isPrime(int n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (int i = 3; i <= sqrt(n); i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

int main() {
  fast_io();

  int t;
  cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    ll z;
    cin >> z;
    int q = sqrt(z);

    ll a, b, c;
    if (isPrime(q)) {
      c = q + 1;
      while (!isPrime(c)) c++;
      b = q, a = q - 1;
      while (!isPrime(a)) a--;
    }
    else {
      c = q;
      while (!isPrime(c)) c++;
      b = c - 1;
      while (!isPrime(b)) b--;
      a = b - 1;
      while (!isPrime(a)) a--;
    }

    ll ans;
    if (b * c <= z) ans = b * c;
    else ans = a * b;
    cout << "Case #" << tc << ": " << ans << "\n";
  }
}
