#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n;
  cin >> n;

  vector<int> A(n), B(n, -1), u;
  vector<bool> vis(n + 1, false);
  for (int i = 0; i < n; i++) {
    cin >> A[i];
    u.push_back(A[i]);
  }

  compress(u);
  if (u.size() == 1) {
    return cout << "NO\n", []{}();
  }

  map<int, int> p;
  for (int i = 0; i < u.size(); i++) {
    p[u[i]] = u[(i + 1) % u.size()];
  }

  cout << "YES\n";
  for (int i = 0; i < n; i++) {
    if (p.count(A[i])) {
      B[i] = p[A[i]];
      vis[B[i]] = true;
      p.erase(A[i]);
    }
  }

  int l = 1;
  for (int i = 0; i < n; i++) {
    if (B[i] != -1) continue;

    while (vis[l]) l++;
    B[i] = l;
    vis[l] = true;
  }

  for (int i = 0; i < n; i++) {
    cout << B[i] << ' ';
    assert(B[i] != A[i]);
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
