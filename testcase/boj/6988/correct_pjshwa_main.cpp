#include <bits/stdc++.h>
typedef long long ll;
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3000;
vector<pii> d[MAX];
int a[MAX];
ll mx = 0;

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int i = 1; i < n; i++) {
    for (int j = i - 1; j >= 0; j--) {
      int diff = a[i] - a[j];
      auto it = lower_bound(d[j].begin(), d[j].end(), pii(diff, -1));
      int nxt;
      if (it != d[j].end() && it->first == diff) nxt = it->second + 1;
      else nxt = 1;
      if (nxt >= 2) {
        mx = max(
          mx,
          (ll)(nxt + 1) * a[i] - (ll)diff * nxt * (nxt + 1) / 2
        );
      }
      d[i].push_back(pii(diff, nxt));
    }
  }

  cout << mx << '\n';
}
