#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int u[MAX];
int l, k, c;

void solve() {
  cin >> l >> k >> c;
  for (int i = 0; i < k; i++) cin >> u[i];
  sort(u, u + k);

  int left = 1, right = l + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    int cnt = 0, last = 0, mlen = 0;
    for (int i = 0; i < k - 1; i++) {
      if (u[i + 1] - last > mid) {
        cnt++;
        mlen = max(mlen, u[i] - last);
        last = u[i];
      }
    }
    if (l - last > mid) {
      cnt++;
      mlen = max(mlen, u[k - 1] - last);
      last = u[k - 1];
    }
    mlen = max(mlen, l - last);

    if (cnt <= c && mlen <= mid) right = mid;
    else left = mid + 1;
  }

  cout << left << ' ';
  int last = l, cnt = 0;
  for (int i = k - 1; i >= 1; i--) {
    if (last - u[i - 1] > left) cnt++, last = u[i];
  }
  if (last > left) cnt++, last = u[0];
  if (cnt < c) last = u[0];
  cout << last << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
