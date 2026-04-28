#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e3;
int cnt[MAX];
int main() {
  fast_io();

  int t;
  cin >> t;

  while (t--) {
    memset(cnt, 0, sizeof(cnt));
    ll n, m;
    cin >> n >> m;

    while (m--) {
      int si, ti;
      cin >> si >> ti;
      cnt[si - 1]++;
      cnt[ti - 1]++;
    }

    ll s = 0;
    for (int i = 0; i < n; i++) s += (n - 1 - cnt[i]) * cnt[i];
    cout << n * (n - 1) * (n - 2) / 6 - s / 2 << '\n';
  }
}
