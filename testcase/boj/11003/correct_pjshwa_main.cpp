#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

pii a[5'000'000];
int main() {
  fast_io();

  int n, l;
  cin >> n >> l;

  int s = 0, e = 0, k;
  for (int i = 0; i < n; i++) {
    cin >> k;
    if (s < e && a[s].second == i - l) s++;
    while (s < e && a[e - 1].first >= k) e--;
    a[e++] = {k, i};
    cout << a[s].first << ' ';
  }
}
