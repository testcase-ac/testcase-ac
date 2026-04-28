#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n) {
  if (n % 2 == 0) return false;
  for (int i = 3; i <= sqrt(n); i += 2) {
    if (n % i == 0) return false;
  }

  return true;
}

void dfs(int cnum, int d) {
  if (d == 0) cout << cnum << '\n';
  else {
    if (isPrime(cnum * 10 + 1)) dfs(cnum * 10 + 1, d - 1);
    if (isPrime(cnum * 10 + 3)) dfs(cnum * 10 + 3, d - 1);
    if (isPrime(cnum * 10 + 7)) dfs(cnum * 10 + 7, d - 1);
    if (isPrime(cnum * 10 + 9)) dfs(cnum * 10 + 9, d - 1);
  }
}

int main() {
  int n;
  cin >> n;
  n--;

  dfs(2, n);
  dfs(3, n);
  dfs(5, n);
  dfs(7, n);
}
