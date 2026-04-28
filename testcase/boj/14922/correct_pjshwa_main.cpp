#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

long long a[1'000'000];
int main() {
  fast_io();

  int n;
  cin >> n;

  long long mv2, mv3, mi2 = -1, mi3 = -1;
  mv2 = mv3 = 2.1e9 + 1;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n - 1; i++) {
    if (mv2 > a[i] + a[i + 1]) {
      mi2 = i;
      mv2 = a[i] + a[i + 1];
    }
  }
  for (int i = 0; i < n - 2; i++) {
    if (mv3 > a[i] + a[i + 1] + a[i + 2]) {
      mi3 = i;
      mv3 = a[i] + a[i + 1] + a[i + 2];
    }
  }

  int mi;
  if (3 * mv2 == 2 * mv3) mi = min(mi2, mi3);
  else {
    if (3 * mv2 < 2 * mv3) mi = mi2;
    else mi = mi3;
  }

  cout << mi << '\n';
}
