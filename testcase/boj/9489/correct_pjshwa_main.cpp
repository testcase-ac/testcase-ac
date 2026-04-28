#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX];
int parent[MAX];
int n, k;

void solve() {
  for (int i = 0; i < n; i++) cin >> a[i];

  if (n == 1) return cout << "0\n", void();

  queue<int> tq;
  tq.push(0);
  parent[0] = -1;

  int last = a[1] - 1, target;
  for (int i = 1; i < n; i++) {
    if (last + 1 < a[i]) tq.pop();

    parent[i] = tq.front();
    tq.push(i);
    last = a[i];

    if (a[i] == k) target = i;
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (parent[i] == -1 || parent[target] == -1) continue;
    if (parent[i] != parent[target] && parent[parent[i]] == parent[parent[target]]) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> k;
    if (n == 0 && k == 0) break;
    solve();
  }
}
