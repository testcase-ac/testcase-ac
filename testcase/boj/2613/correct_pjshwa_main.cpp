#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300;
int a[MAX];
int n, m;

bool check(int t) {
  int cnt = 1, rsum = 0;
  for (int i = 0; i < n; i++) {
    if (rsum + a[i] <= t) rsum += a[i];
    else {
      cnt++;
      rsum = a[i];
    }
  }
  return cnt <= m;
}

void solve() {
  cin >> n >> m;

  int left = 0;
  for (int i = 0; i < n; i++) cin >> a[i], left = max(left, a[i]);

  int right = 1e9;
  while (left < right) {
    int mid = (left + right) / 2;
    if (check(mid)) right = mid;
    else left = mid + 1;
  }

  cout << left << '\n';
  int rsum = 0, li = 0;
  vector<int> chunks;
  for (int i = 0; i < n; i++) {
    if (rsum + a[i] <= left) rsum += a[i];
    else {
      chunks.push_back(i - li);
      li = i;
      rsum = a[i];
    }
  }
  chunks.push_back(n - li);

  int rem = max(0, m - (int)chunks.size());
  for (int chunk : chunks) {
    while (rem && chunk > 1) {
      cout << "1 ";
      rem--; chunk--;
    }
    cout << chunk << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
