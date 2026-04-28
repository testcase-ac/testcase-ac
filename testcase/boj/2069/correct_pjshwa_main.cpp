#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 33000;
int s[MAX], e[MAX];
multiset<int> from[MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x1, x2;
    cin >> x1 >> x2;
    s[x1]++;
    e[x2]++;
    from[x2].insert(x1);
  }

  ll ans = 0;
  multiset<int> cur;
  for (ll i = 0; i < MAX; i++) {
    for (int j = 0; j < s[i]; j++) cur.insert(i);
    for (int j = 0; j < e[i]; j++) {
      auto sit = cur.lower_bound(*from[i].begin());
      if (sit == cur.begin()) {
        int si = *sit;
        sit++;
        int ei;
        if (sit == cur.end()) ei = i;
        else ei = *sit;
        ans += (i - si) * (i - si) - (i - ei) * (i - ei);
      }
      cur.erase(cur.find(*from[i].begin()));
      from[i].erase(from[i].begin());
    }
  }

  cout << ans << '\n';
}
