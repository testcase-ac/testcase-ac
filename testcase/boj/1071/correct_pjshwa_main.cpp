#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(false);
}

int a[50];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  for (int i = 0; i < n - 1; i++) {
    if (a[i] + 1 == a[i + 1]) {
      int j = i + 1;
      while (j < n && a[i + 1] == a[j]) j++;

      if (j < n) swap(a[i + 1], a[j]);
    }
  }

  bool flag = false;
  for (int i = 0; i < n - 1; i++) flag |= (a[i] + 1 == a[i + 1]);

  if (flag) {
    int v1 = n - 1;
    while (a[v1] == a[v1 - 1]) v1--;

    int v2 = v1 - 1;
    while (v2 > 0 && a[v2] == a[v2 - 1]) v2--;

    for (int i = 0; i < v2; i++) cout << a[i] << ' ';
    for (int i = v1; i < n; i++) cout << a[i] << ' ';
    for (int i = v2; i < v1; i++) cout << a[i] << ' ';
  }
  else {
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
  }

}
