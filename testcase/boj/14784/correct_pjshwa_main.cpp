#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e6;
int lp[MAX + 1], vis[MAX + 1];
bool vis2[MAX + 1];

int nxt(int ox) {
  int x = ox;
  map<int, int> pf;
  while (x > 1) {
    pf[lp[x]]++;
    x /= lp[x];
  }

  ll dst = 1;
  for (auto [k, v] : pf) {
    ll pow = 1;
    for (int i = 0; i < v + 1; i++) pow *= k;
    dst *= (pow - 1) / (k - 1);
  }
  dst -= ox;
  if (dst > MAX) return -1;
  return dst;
}

void dfs(int node) {
  int dst = nxt(node);
  if (dst == -1) return;

  if (node == dst) vis[node] = 2;
  else {
    vis[node] = -1;

    // Cycle is detected
    if (vis[dst] == -1) {
      vis[dst] = 2;
      int s = nxt(dst);
      while (s != dst) {
        vis[s] = 2;
        s = nxt(s);
      }
    }
    else {
      if (!vis[dst]) dfs(dst);
      if (vis[node] != 2) vis[node] = 1;
    }
  }
}

bool si;
int sv;
vector<int> current;

void dfs2(int node) {
  vis2[node] = true;
  current.push_back(node);
  int dst = nxt(node);
  if (dst < sv) return si = false, void();
  if (!vis2[dst]) dfs2(dst);
}

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

  int s, e;
  cin >> s >> e;
  
  for (int i = s; i <= e; i++) {
    if (!vis[i]) dfs(i);
  }

  for (int i = s; i <= e; i++) {
    if (!vis2[i] && vis[i] == 2) {
      si = true, sv = i;
      dfs2(i);
      if (si) {
        for (auto x : current) cout << x << " ";
        cout << '\n';
      }
      current.clear();
    }
  }
}
