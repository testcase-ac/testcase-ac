#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}
ll bi(int i, int j);
ll bs(int i, int j);

const ll MIN = -(1e18 + 1);
int arr[5001];
ll a[5001][5001], b[5001][5001];
ll bi(int i, int j) {
  if (a[i][j] == MIN) {
    if (i == j) a[i][j] = accumulate(arr + 1, arr + i + 1, 0LL);
    else a[i][j] = max(bi(i - 1, j), bs(i - 1, j - 1)) + arr[i];
  }
  return a[i][j];
}

ll bs(int i, int j) {
  if (j == 0) return 0;

  if (b[i][j] == MIN) {
    if (i == j) b[i][j] = bi(i, j);
    else b[i][j] = max(bs(i - 1, j), bi(i, j));
  }
  return b[i][j];
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    for (int j = 1; j <= n; j++) a[i][j] = b[i][j] = MIN;
  }

  cout << bs(n, k) << '\n';
}
