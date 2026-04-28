#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool isPrime(int n) {
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (int i = 3; i <= sqrt(n); i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  while (!isPrime(n)) n--;
  cout << n;
}
