#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int x[(int)1e5];
int a[(int)1e5];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> a[i];
    x[i] += 1e9;
  }

  ll s, left = 0, right = 2e9;
  ll mid = (left + right) / 2;
  while (left < right) {
    s = 0;
    for (int i = 0; i < n; i++) s += (abs(x[i] - mid - 1) - abs(x[i] - mid)) * a[i];
    if (s >= 0) right = mid;
    else left = mid + 1;
    mid = (left + right) / 2;
  }

  mid -= 1e9;
  cout << mid << '\n';
}
