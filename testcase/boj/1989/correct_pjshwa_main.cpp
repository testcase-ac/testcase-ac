#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
ll a[MAX + 1];
ll mv = -1;
int ml, mr;

void update_global(int cl, int cr, ll res) {
  if (res > mv) {
    mv = res;
    ml = cl;
    mr = cr;
  }
}

ll rec(int s, int e) {
  ll res;
  if (s == e) res = 0;
  else if (s + 1 == e) {
    ll val = a[s] - a[s - 1];
    res = val * val;
    update_global(s, s, res);
  }
  else {
    int mid = (s + e) / 2;
    res = max(rec(s, mid), rec(mid, e));

    ll h = a[mid] - a[mid - 1];
    int l = mid, r = mid;
    while (r - l + 1 < e - s) {
      int p = l > s ? min(h, a[l - 1] - a[l - 2]) : -1;
      int q = r < e - 1 ? min(h, a[r + 1] - a[r]) : -1;
      if (p >= q) {
        h = p;
        l--;
      }
      else {
        h = q;
        r++;
      }
      if ((a[r] - a[l - 1]) * h > res) {
        res = (a[r] - a[l - 1]) * h;
        update_global(l, r, res);
      }
    }
  }
  return res;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i], a[i] += a[i - 1];
  cout << rec(1, n + 1) << '\n';
  cout << ml << " " << mr << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
