#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5;
int a[MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  bool downhill = false;
  for (int i = 0; i < n - 1; i++) {
    if (downhill) {
      if (a[i] <= a[i + 1]) {
        cout << "NO";
        return 0;
      }
    }
    else {
      if (a[i] == a[i + 1]) {
        cout << "NO";
        return 0;
      }
      else if (a[i] > a[i + 1]) downhill = true;
    }
  }
  cout << "YES";
}
