#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX + 1], parent[MAX + 1];
vector<int> cc[MAX + 1];
int inv[MAX + 1];
bool vis[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> a[i];
    parent[i] = i;
  }

  stack<int> s;
  for (int i = 1; i <= N; i++) {
    
    if (!s.empty() && s.top() > a[i]) {
      int smax = 0;
      while (!s.empty() && s.top() > a[i]) {
        Union(s.top(), a[i]);
        smax = max(smax, s.top());
        s.pop();
      }
      s.push(smax);
    }

    if (s.empty() || a[i] > s.top()) s.push(a[i]);
  }

  for (int i = 1; i <= N; i++) cc[Find(i)].push_back(i), inv[i] = Find(i);

  int sz = 0;
  for (int i = 1; i <= N; i++) {
    if (cc[i].empty()) continue;
    sz++;
    sort(cc[i].begin(), cc[i].end());
  }

  cout << sz << '\n';
  for (int i = 1; i <= N; i++) {
    if (vis[i]) continue;

    cout << cc[inv[i]].size() << ' ';
    for (int e : cc[inv[i]]) {
      vis[e] = true;
      cout << e << ' ';
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
