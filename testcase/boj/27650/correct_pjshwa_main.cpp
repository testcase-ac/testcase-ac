#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 5e6;
ll lp[MAX + 1];
vector<int> pr;

int ask(int n) {
  cout << "? " << n << endl;
  int res; cin >> res;
  return res;
}

void solve() {
  int N; cin >> N;

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= N; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; j++)
      lp[i * pr[j]] = pr[j];
  }

  // Only candidates are primes
  int l = 0, r = pr.size();
  while (l < r) {
    int m = (l + r) / 2;
    if (ask(pr[m])) l = m + 1;
    else r = m;
  }

  cout << "! " << pr[l] << endl;
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
