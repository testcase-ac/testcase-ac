#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int lp[MAX + 1], h[10];
vector<int> pr, ans;
vector<int> current;
int n, m, sum = 0;

void dfs(int i) {
  if (i == n) {
    if (current.size() == m && lp[sum] == sum) ans.push_back(sum);
    return;
  }
  dfs(i + 1);
  current.push_back(h[i]);
  sum += h[i];
  dfs(i + 1);
  current.pop_back();
  sum -= h[i];
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> h[i];

  dfs(0);
  compress(ans);

  if (ans.size()) for (int e : ans) cout << e << ' ';
  else cout << -1;
  cout << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
