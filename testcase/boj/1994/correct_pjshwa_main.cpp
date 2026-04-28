#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
vector<pii> d[MAX];
int a[MAX];
int mx = 0;

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  for (int i = 1; i < n; i++) {
    for (int j = i - 1; j >= 0; j--) {
      int diff = a[i] - a[j];
      auto it = lower_bound(d[j].begin(), d[j].end(), pii(diff, -1));
      int nxt;
      if (it != d[j].end() && it->first == diff) nxt = it->second + 1;
      else nxt = 1;
      mx = max(mx, nxt);
      d[i].push_back(pii(diff, nxt));
    }
  }

  cout << mx + 1 << '\n';
}
