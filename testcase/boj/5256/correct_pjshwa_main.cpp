#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5 + 50;
int a[MAX], b[MAX];
bool vis[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> b[i];

  a[0] = b[0];
  vis[a[0]] = 1;

  int sp = 1, ep = 2 * n - 1;
  for (int i = 1; i < n; i++) {
    if (b[i - 1] == b[i]) {
      while (vis[sp]) sp++;
      a[2 * i - 1] = sp++;
      vis[a[2 * i - 1]] = 1;
      while (vis[ep]) ep--;
      a[2 * i] = ep--;
      vis[a[2 * i]] = 1;
    }
    if (b[i - 1] < b[i]) {
      if (vis[b[i]]) {
        while (vis[ep]) ep--;
        a[2 * i - 1] = ep--;
        vis[a[2 * i - 1]] = 1;
        while (vis[ep]) ep--;
        a[2 * i] = ep--;
        vis[a[2 * i]] = 1;
      }
      else {
        a[2 * i - 1] = b[i];
        vis[a[2 * i - 1]] = 1;
        while (vis[ep]) ep--;
        a[2 * i] = ep--;
        vis[a[2 * i]] = 1;
      }
    }
    if (b[i - 1] > b[i]) {
      if (vis[b[i]]) {
        while (vis[sp]) sp++;
        a[2 * i - 1] = sp++;
        vis[a[2 * i - 1]] = 1;
        while (vis[sp]) sp++;
        a[2 * i] = sp++;
        vis[a[2 * i]] = 1;
      }
      else {
        a[2 * i - 1] = b[i];
        vis[a[2 * i - 1]] = 1;
        while (vis[sp]) sp++;
        a[2 * i] = sp++;
        vis[a[2 * i]] = 1;
      }
    }
  }

  for (int i = 0; i < 2 * n - 1; i++) cout << a[i] << " ";
  cout << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
