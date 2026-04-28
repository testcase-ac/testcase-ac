#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int n;
pii a[100000];
int do_search(int d) {
  int prev = -d;
  bool able = true;
  for (int i = 0; i < n; i++) {
    if (prev + d <= a[i].first + a[i].second) prev = max(prev + d, a[i].first);
    else able = false;
  }
  return able;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
  sort(a, a + n);

  ll left = 1, right = 2e9 + 1;
  ll mid = (left + right) / 2;

  while (left < right) {
    if (do_search(mid)) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }
  cout << mid - 1 << '\n';
}
