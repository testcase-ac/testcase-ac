#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[500'001];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  sort(a + 1, a + n + 1);

  long long b = 0;
  for (int i = 1; i <= n; i++) b += abs(i - a[i]);
  cout << b;
}
