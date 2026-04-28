#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int o[10];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> o[i];

  vector<int> ans;
  ans.push_back(n);

  for (int i = n - 1; i >= 1; i--) ans.insert(ans.begin() + o[i - 1], i);
  for (int e : ans) cout << e << ' ';
}
