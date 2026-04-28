#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[5000];
bool v[400001];
int main() {
  fast_io();

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) cin >> a[i];

  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (v[a[i] - a[j] + 200000]) {
        cnt++;
        break;
      }
    }

    for (int j = 0; j <= i; j++) v[a[i] + a[j] + 200000] = true;
  }

  // TLE: O(n^2 logn^2)
  // set<int> two_sums;
  // map<int, int> minpos;
  // for (int i = 0; i < n; i++) {
  //   for (int j = i; j < n; j++) {
  //     int s = a[i] + a[j];
  //     two_sums.insert(s);

  //     auto found = minpos.find(s);
  //     if (found != minpos.end()) found->second = min(found->second, j);
  //     else minpos.insert({s, j});
  //   }
  // }

  // for (int i = n - 1; i >= 0; i--) {
  //   for (int j = i - 1; j >= 0; j--) {
  //     if (two_sums.count(a[i] - a[j]) && minpos[a[i] - a[j]] < i) {
  //       cnt++;
  //       break;
  //     }
  //   }
  // }

  cout << cnt << '\n';
}
