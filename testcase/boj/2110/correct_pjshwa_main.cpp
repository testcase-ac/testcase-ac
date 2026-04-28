#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[200000];

int do_search(int d) {
  int c = 1, i = 0;
  int rem = d;
  while (i < 200000 - 1) {
    rem -= (a[i + 1] - a[i]);
    if (rem <= 0) {
      c++;
      rem = d;
    }
    i++;
  }
  return c;
}

int main() {
  fast_io();

  int n, c;
  cin >> n >> c;

  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  int left = 1, right = 1e9 + 1;
  int mid = (left + right) / 2;

  while (left < right) {
    if (do_search(mid) >= c) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }
  cout << mid - 1 << '\n';
}
