#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool isPrime(int n) {
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (int i = 3; i <= sqrt(n); i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

bool isComposite(int n) {
  return n != 1 && !isPrime(n);
}

int main() {
  vector<int> pr;

  int n, k1, k2, k3;
  cin >> n;

  bool able;
  if (n >= 4) able = true;
  else if (n == 3) {
    cin >> k1 >> k2 >> k3;
    able = !(k1 == 1 && k2 == 1 && k3 == 1);
  }
  else if (n == 2) {
    cin >> k1 >> k2;
    k3 = k1 + k2;
    able = isComposite(k1) || isComposite(k2) || isComposite(k3);
  }
  else {
    cin >> k1;
    able = isComposite(k1);
  }

  cout << (able ? "Yes" : "No");
}
