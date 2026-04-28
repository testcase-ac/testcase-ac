#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int s[MAX + 1];
vector<int> gaps[MAX + 1];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    int si, ei;
    cin >> si >> ei;
    s[si]++;
    gaps[ei].push_back(ei - si + 1);
  }

  ll cdt = 0, cw = 0;
  for (int i = 1; i <= k; i++) {
    cw += s[i];
    cdt += cw;
    cout << cdt << ' ';
    
    for (int e : gaps[i]) {
      cw--;
      cdt -= e;
    }
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
