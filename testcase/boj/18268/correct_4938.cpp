#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define int long long
int arr[10][20];
int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int k, n;
  cin >> k >> n;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < n; j++) {
      cin >> arr[i][j];
    }
  }
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      int r = find(arr[0], arr[0] + n, i) < find(arr[0], arr[0] + n, j);
      bool ok = 1;
      for (int t = 1; t < k; t++) {
        if (find(arr[t], arr[t] + n, i) < find(arr[t], arr[t] + n, j) != r) {
          ok = 0;
        }
      }
      cnt += ok;
    }
  }
  cout << cnt;
}
