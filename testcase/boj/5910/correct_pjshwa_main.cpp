#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  vector<pii> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
  sort(a.begin(), a.end(), [](pii a, pii b) {
    if (a.first < a.second) {
      return b.first < b.second ? a.first < b.first : true;
    }
    else {
      return b.first > b.second ? a.second > b.second : false;
    }
  });

  vector<int> cow_entry(n), cow_exit(n);
  cow_entry[0] = a[0].first;
  cow_exit[0] = a[0].first + a[0].second;
  for (int i = 1; i < n; ++i) cow_entry[i] = cow_entry[i - 1] + a[i].first;
  for (int i = 1; i < n; ++i) cow_exit[i] = max(cow_entry[i], cow_exit[i - 1]) + a[i].second;
  cout << cow_exit[n - 1] << '\n';
}
