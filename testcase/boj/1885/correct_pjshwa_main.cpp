#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  int m = 0;
  set<int> s;
  for (int i = 0; i < n; i++) {
    s.insert(a[i]);
    if (s.size() == k) {
      m++;
      s.clear();
    }
  }

  cout << m + 1 << '\n';
}
