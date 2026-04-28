#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> oposs[MAX];

void solve() {
  int n, k;
  cin >> n >> k;

  vector<string> vs(k);
  for (int i = 0; i < k; ++i) cin >> vs[i];

  for (int i = 0; i < n; i++) {
    set<int> oneg;
    for (int j = 0; j < k; j++) oneg.insert(vs[j][i] - 'a');
    for (int j = 0; j < 26; j++) {
      if (oneg.count(j)) continue;
      oposs[i].push_back(j);
    }
  }

  string a, b, c(n, '0');
  cin >> a >> b;

  bool carry = false;
  for (int i = n - 1; i >= 0; i--) {
    int ax = lower_bound(oposs[i].begin(), oposs[i].end(), a[i] - 'a') - oposs[i].begin();
    int bx = lower_bound(oposs[i].begin(), oposs[i].end(), b[i] - 'a') - oposs[i].begin();
    int nx = ax + bx + carry;
    carry = false;

    int sz = oposs[i].size();
    if (nx >= sz) {
      nx -= sz;
      carry = true;
    }
    c[i] = oposs[i][nx] + 'a';
  }

  cout << c << '\n';
}

int main() {
  fast_io();
  
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
