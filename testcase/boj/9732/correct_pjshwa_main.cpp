#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 10000;
int lp[MAXN + 1];
vector<int> pr;

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, M, ans = 0; cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    int sum = 0, x;
    for (int j = 0; j < M; ++j) {
      cin >> x; int cnt = 0;
      while (x > 1) {
        x /= lp[x];
        cnt++;
      }
      sum += cnt;
    }
    ans ^= sum;
  }

  if (ans) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXN; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXN; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
