#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX + 1];

void solve() {
  int n, k, r;
  cin >> n >> k >> r;
  while (k--) {
    int x;
    cin >> x;
    A[x] = 1;
  }

  int s = 0;
  for (int i = 1; i <= r; i++) s += A[i];
  
  int i = r, ans = 0;
  while (s < 2) {
    if (!A[i]) A[i] = 1, s++, ans++;
    i--;
  }

  for (int i = r + 1; i <= n; i++) {
    s -= A[i - r];
    s += A[i];
    if (s < 2) A[i] = 1, s++, ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
