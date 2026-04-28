#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[2000], lis[2000], lds[2000];
int main() {
  fast_io();

  int n;
  cin >> n;

  for(int i = 0; i < n; i++) cin >> a[i];
  reverse(a, a + n);

  lis[0] = lds[0] = 1;
  for(int i = 1; i < n; i++) {
    lis[i] = lds[i] = 1;
    for (int j = i - 1; j >= 0; j--) {
      if (a[i] > a[j]) lis[i] = max(lis[i], lis[j] + 1);
      if (a[i] < a[j]) lds[i] = max(lds[i], lds[j] + 1);
    }
  }

  int mv = 0;
  for(int i = 0; i < n; i++) mv = max(mv, lis[i] + lds[i] - 1);

  cout << mv << '\n';
}
