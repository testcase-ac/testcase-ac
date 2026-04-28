#include <bits/stdc++.h> 
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;

  int ans[n + 1];
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    ans[x] = x - i;
  }
  for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
}
