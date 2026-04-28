#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[200000], mp[200000];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  if (n == 1) {
    cout << 1;
    return 0;
  }

  mp[n - 1] = 0;
  for (int i = n - 2; i >= 0; i--) mp[i] = max(mp[i + 1] - 1, a[i + 1] + 1);

  vector<int> champs;
  for (int i = 1; i < n; i++) {
    if (a[i] > a[i - 1] && a[i] + i >= mp[i]) champs.push_back(i + 1);
  }

  if (champs.size()) {
    for (auto c : champs) cout << c << ' ';
  }
  else cout << -1;
}
