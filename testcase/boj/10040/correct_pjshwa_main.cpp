#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int votes[MAX], cost[MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> cost[i];

  while (m--) {
    int l;
    cin >> l;
    for (int i = 0; i < n; i++) {
      if (cost[i] <= l) {
        votes[i]++;
        break;
      }
    }
  }

  int mi = 0, mv = 0;
  for (int i = 0; i < n; i++) {
    if (votes[i] > mv) {
      mv = votes[i];
      mi = i;
    }
  }
  cout << mi + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
