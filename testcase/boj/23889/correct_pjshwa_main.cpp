#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX], r[MAX];

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  ll s = 0;
  for (int i = 0; i < n; i++) cin >> a[i], s += a[i];
  for (int i = 0; i < k; i++) cin >> r[i], r[i]--;

  priority_queue<pll> sv;
  ll seg;
  for (int i = 0; i < k - 1; i++) {
    seg = 0;
    for (int j = r[i]; j < r[i + 1]; j++) seg += a[j];
    sv.push({seg, -(r[i] + 1)});
  }
  seg = 0;
  for (int j = r[k - 1]; j < n; j++) seg += a[j];
  sv.push({seg, -(r[k - 1] + 1)});

  set<int> ans;
  while (m--) {
    auto [seg, l] = sv.top();
    sv.pop();
    ans.insert(-l);
  }
  for (auto i : ans) cout << i << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
