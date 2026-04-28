#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int a[MAX];

void solve() {
  int n, l;
  cin >> n >> l;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  for (int i = 0; i < n - 1; i++) {
    
    int left = i + 1, right = n - left;
    
  }



}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
