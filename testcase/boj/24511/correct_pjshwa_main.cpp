#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX], b[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];

  // 나도리메롱
  queue<int> q;
  for (int i = n - 1; i >= 0; i--) {
    if (a[i]) continue;
    q.push(b[i]);
  }

  int m;
  cin >> m;
  while (m--) {
    int x;
    cin >> x;
    q.push(x);

    cout << q.front() << ' ';
    q.pop();
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
