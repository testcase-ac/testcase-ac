#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int cnt;
int ask(int x, int k) {
  cnt++;

  cout << "? " << x << ' ' << k << endl;
  int ret; cin >> ret;
  return ret;
}

const int MAX = 1000, MAXP = 3e6;
int ans[MAX + 1];
vector<int> adj[MAX + 1];

int lp[MAXP + 1];
vector<int> pr;

void dfs(int u) {
  int v = adj[u].back();
  ans[u] = v;
  if (ans[v] == 0) dfs(v);
}

void solve() {
  int N; cin >> N;

  queue<int> prime_q; int lp = 0;
  for (int p : pr) {
    if (p <= N) continue;
    if (prime_q.size() == N) break;
    if (lp + N > p) continue;
    prime_q.push(p); lp = p;
  }
  assert(prime_q.size() == N);

  for (int i = 1; i <= N; i++) {
    if (ans[i] != 0) continue;

    int k = prime_q.front(); prime_q.pop();

    vector<int> P;
    P.push_back(ask(i, k++));

    if (P[0] == i) {
      ans[i] = i;
      continue;
    }

    while (int ret = ask(i, k++)) {
      P.push_back(ret);
      if (ret == P[0]) break;
    }

    for (int i = 1; i < P.size(); i++) {
      int u = P[i - 1], v = P[i];
      adj[u].push_back(v);
    }

    dfs(i);
  }

  cout << "! ";
  for (int i = 1; i <= N; i++) cout << ans[i] << ' ';
  cout << endl;
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXP; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXP; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
