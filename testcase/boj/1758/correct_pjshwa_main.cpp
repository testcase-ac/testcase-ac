#include <bits/stdc++.h>
using namespace std;

int a[100000];
int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);
  reverse(a, a + n);

  long long t = 0;
  for (int i = 0; i < n; i++) t += max(0, a[i] - i);
  cout << t << '\n';
}
