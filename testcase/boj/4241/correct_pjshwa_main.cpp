#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, MAXV = 1e6;
int n, m, d;
int vis[MAXN + 1], lp[MAXV + 1];
vector<int> pr;

bool is_prime(int x) {
  if (x < 2) return false;
  return lp[x] == x;
}

vector<int> cur; int f = 0;
void dfs(int i, int sum) {
  if (f) return;

  if (i == m - n + 1) {
    for (int j = 0; j < cur.size(); ++j) {
      if (j) cout << ',';
      cout << cur[j];
    }
    cout << '\n';
    f = 1;
  }
  else {
    for (int nxt = n; nxt <= m; ++nxt) {
      if (vis[nxt]) continue;

      bool ok = 1; int Z = cur.size(), acc = nxt;
      for (int j = 0; j < d - 1; ++j) {
        if (j >= Z) break;
        acc += cur[Z - j - 1];
        if (is_prime(acc)) ok = 0;
      }

      if (ok) {
        vis[nxt] = 1;
        cur.push_back(nxt);
        dfs(i + 1, sum + nxt);
        cur.pop_back();
        vis[nxt] = 0;
      }
    }
  }
}

void solve() {
  f = 0; dfs(0, 0);
  if (f == 0) cout << "No anti-prime sequence exists.\n";
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXV; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXV; j++)
      lp[i * pr[j]] = pr[j];
  }

  while (cin >> n >> m >> d) {
    if (n == 0 && m == 0 && d == 0) break;
    solve();
  }
}
