#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const ll MAX = 1e3;
ll lp[MAX + 1];

int main() {
  fast_io();

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

  int t, n;
  cin >> t;

  while (t--) {
    cin >> n;

    n -= 3;
    vector<int> ans;
    for (int a = n / 2; a >= 2; a--) {
      if (lp[a] == a && lp[n - a] == n - a) {
        ans.push_back(a);
        ans.push_back(n - a);
        ans.push_back(3);
        sort(ans.begin(), ans.end());
        for (int el : ans) cout << el << ' ';
        cout << '\n';
        break;
      }
    }
  }
}
