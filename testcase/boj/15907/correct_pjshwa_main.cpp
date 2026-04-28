#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e6;
int lp[MAX + 1], a[MAX], rem[MAX];

int main() {
  vector<int> pr;

  // Sieve of Eratosthenes O(n)
  for (int i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  int ans = 0;
  for (int p : pr) {
    for (int i = 0; i < n; i++) {
      rem[a[i] % p]++;
      ans = max(ans, rem[a[i] % p]);
    }
    for (int i = 0; i < n; i++) rem[a[i] % p]--;
  }
  cout << ans;
}
