#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAX = 4e6;
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

  int n, sz = pr.size();
  cin >> n;

  ll sum, cnt = 0;
  for (int i = sz - 1; i >= 0; i--) {
    sum = 0;
    for (int j = i; j >= 0; j--) {
      sum += pr[j];
      if (sum >= n) {
        if (sum == n) cnt++;
        break;
      }
    }
  }

  cout << cnt << '\n';
}
