#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int a[MAX];
priority_queue<int> wait[100'005];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);
  reverse(a, a + n);

  ll score = 0;
  for (int i = 0; i < n; i++) {
    if (wait[a[i] + 1].size()) {
      int val = wait[a[i] + 1].top();
      score += val;
      wait[a[i] + 1].pop();
      wait[a[i]].push(val);
    }
    else {
      score += a[i];
      wait[a[i]].push(a[i]);
    }
  }

  cout << score << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
