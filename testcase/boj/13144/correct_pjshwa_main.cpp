#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  unordered_map<int, int> m;
  long long ans = 0;
  int lb = 0;
  for (int i = 0; i < n; i++) {
    if (m.count(a[i])) lb = max(lb, m[a[i]] + 1);
    m[a[i]] = i;
    ans += (i - lb + 1);
  }

  cout << ans << '\n';
}
