#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAX = 1e6;
ll lp[MAX + 1];

int main() {
  vector<int> pr;

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int n;
  cin >> n;

  if (n < 8) cout << -1;
  else {
    if (n & 1) {
      n -= 5;
      cout << "3 2 ";
    }
    else {
      n -= 4;
      cout << "2 2 ";
    }
    for (int a = n / 2; a >= 2; a--) {
      if (lp[a] == a && lp[n - a] == n - a) {
        cout << a << ' ' << n - a;
        return 0;
      }
    }
  }
}
