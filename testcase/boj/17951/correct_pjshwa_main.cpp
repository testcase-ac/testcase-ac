#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(false);
}

const int MAX = 1e5;
int a[MAX];

int doSearch(int n, int tk) {
  int cs = 0, cc = 0;
  for (int i = 0; i < n; i++) {
    cs += a[i];
    if (cs >= tk) {
      cs = 0;
      cc++;
    }
  }
  return cc;
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  int left = 1, right = 2e6;
  int mid = (left + right) / 2;

  while (left < right) {
    if (doSearch(n, mid) >= k) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }

  cout << mid - 1;
}
