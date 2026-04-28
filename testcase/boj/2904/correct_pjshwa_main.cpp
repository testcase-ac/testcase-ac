#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAX = 1e6;
ll lp[MAX + 1];
int a[100];
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

  int n, s, lpc;
  cin >> n;
  map<int, int> ptally;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) {
    s = a[i];

    while (s != 1) {
      lpc = lp[s];
      s /= lpc;
      if (!ptally.count(lpc)) ptally[lpc] = 0;
      ptally[lpc]++;
    }
  }

  map<int, int> target;
  for (auto[el, cnt] : ptally) target[el] = (cnt / n);

  ll g = 1;
  for (auto[el, cnt] : target) {
    for (int i = 0; i < cnt; i++) g *= el;
  }

  int moves = 0;
  for (int i = 0; i < n; i++) {
    ptally.clear();
    s = a[i];

    while (s != 1) {
      lpc = lp[s];
      s /= lpc;
      if (!ptally.count(lpc)) ptally[lpc] = 0;
      ptally[lpc]++;
    }

    for (auto[el, cnt] : target) {
      if (!ptally.count(el)) ptally[el] = 0;
      moves += max(0, cnt - ptally[el]);
    }
  }

  cout << g << ' ' << moves << '\n';
}
